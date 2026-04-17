#include "Server.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server(int port, const std::string &password)
	: _port(port), _listenFd(-1), _commands(password)
{
}

Server::~Server()
{
	closeAll();
}

void Server::run(const volatile sig_atomic_t &stopFlag)
{
	setupSocket();
	std::cout << "[ft_irc] Listening on port " << _port << std::endl;

	while (!stopFlag)
	{
		fd_set readFds;
		int maxFd = -1;
		buildReadSet(readFds, maxFd);

		struct timeval tv;
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		int ready = select(maxFd + 1, &readFds, NULL, NULL, &tv);
		if (ready < 0)
		{
			if (errno == EINTR)
			{
				continue;
			}
			throw std::runtime_error(std::string("select failed: ") + std::strerror(errno));
		}
		if (ready == 0)
		{
			continue;
		}

		if (FD_ISSET(_listenFd, &readFds))
		{
			acceptClient();
		}

		std::map<int, User>::iterator curr = _users.all().begin();
		while (curr != _users.all().end())
		{
			int fd = curr->first;
			++curr;
			if (FD_ISSET(fd, &readFds))
			{
				handleClientData(fd);
			}
		}
	}

	std::cout << "[ft_irc] Shutting down." << std::endl;
}

void Server::buildReadSet(fd_set &readFds, int &maxFd) const
{
	FD_ZERO(&readFds);
	FD_SET(_listenFd, &readFds);
	maxFd = _listenFd;

	std::map<int, User>::const_iterator it = _users.all().begin();
	for (; it != _users.all().end(); ++it)
	{
		FD_SET(it->first, &readFds);
		if (it->first > maxFd)
		{
			maxFd = it->first;
		}
	}
}

void Server::setupSocket()
{
	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenFd < 0)
	{
		throw std::runtime_error(std::string("socket failed: ") + std::strerror(errno));
	}

	int opt = 1;
	if (setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		throw std::runtime_error(std::string("setsockopt failed: ") + std::strerror(errno));
	}

	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(static_cast<uint16_t>(_port));

	if (bind(_listenFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0)
	{
		throw std::runtime_error(std::string("bind failed: ") + std::strerror(errno));
	}

	if (listen(_listenFd, 42) < 0)
	{
		throw std::runtime_error(std::string("listen failed: ") + std::strerror(errno));
	}
}

void Server::closeAll()
{
	std::map<int, User>::iterator it = _users.all().begin();
	for (; it != _users.all().end(); ++it)
	{
		close(it->first);
	}
	_users.all().clear();

	if (_listenFd >= 0)
	{
		close(_listenFd);
		_listenFd = -1;
	}
}

void Server::acceptClient()
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = accept(_listenFd, reinterpret_cast<struct sockaddr *>(&addr), &len);

	if (fd < 0)
	{
		if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)
		{
			std::cerr << "accept failed: " << std::strerror(errno) << std::endl;
		}
		return;
	}

	_users.add(fd, inet_ntoa(addr.sin_addr));
	User *user = _users.get(fd);

	std::cout << "[ft_irc] Client connected: fd=" << fd << " ip=" << user->ip << std::endl;
	const std::string msg = ":ft_irc NOTICE AUTH :Welcome. Authenticate with PASS <password>\\r\\n";
	send(fd, msg.c_str(), msg.size(), 0);
}

void Server::removeClient(int fd, const std::string &reason)
{
	if (_users.has(fd))
	{
		std::cout << "[ft_irc] Client disconnected: fd=" << fd << " (" << reason << ")" << std::endl;
		close(fd);
		_users.remove(fd);
	}
}

void Server::handleClientData(int fd)
{
	User *user = _users.get(fd);
		if (user == NULL)
	{
		return;
	}

	char buffer[512];
	std::memset(buffer, 0, sizeof(buffer));
	ssize_t count = recv(fd, buffer, sizeof(buffer) - 1, 0);

	if (count <= 0)
	{
		removeClient(fd, count == 0 ? "connection closed" : std::strerror(errno));
		return;
	}

	user->recvBuffer.append(buffer, static_cast<size_t>(count));
	processLines(*user);
}

void Server::processLines(User &user)
{
	std::string::size_type pos = std::string::npos;
	while ((pos = user.recvBuffer.find('\n')) != std::string::npos)
	{
		std::string line = user.recvBuffer.substr(0, pos);
		user.recvBuffer.erase(0, pos + 1);

		line = CommandHandler::trimCrlf(line);
		if (line.empty())
		{
			continue;
		}

		std::string disconnectReason;
		if (_commands.handleLine(user, _users, line, disconnectReason))
		{
			removeClient(user.fd, disconnectReason);
			return;
		}

		if (!_users.has(user.fd))
		{
			return;
		}
	}
}
