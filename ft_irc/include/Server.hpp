#ifndef SERVER_HPP
#define SERVER_HPP

#include "ChannelManager.hpp"
#include "CommandHandler.hpp"
#include "UserManager.hpp"

#include <csignal>
#include <string>
#include <sys/select.h>

class Server
{
public:
	Server(int port, const std::string &password);
	~Server();

	void run(const volatile sig_atomic_t &stopFlag);

private:
	int _port;
	int _listenFd;
	UserManager _users;
	ChannelManager _channels;
	CommandHandler _commands;

	void setupSocket();
	void closeAll();

	void acceptClient();
	void removeClient(int fd, const std::string &reason);

	void handleClientData(int fd);
	void processLines(User &user);
	void buildReadSet(fd_set &readFds, int &maxFd) const;
};

#endif
