#include "CommandHandler.hpp"
#include "ErrorReplies.hpp"

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <sys/socket.h>

CommandHandler::CommandHandler(const std::string &password)
	: _password(password)
{
}

bool CommandHandler::handleLine(User &user, UserManager &users, const std::string &line, std::string &disconnectReason) const
{
	disconnectReason.clear();

	std::istringstream iss(line);
	std::string cmd;
	iss >> cmd;
	cmd = upper(cmd);

	if (cmd.empty())
	{
		return false;
	}

	if (dispatchCommand(cmd, user, users, iss, disconnectReason))
	{
		return !disconnectReason.empty();
	}

	if (!user.passOk)
	{
		sendRaw(user.fd, ErrorReplies::notRegistered());
		return false;
	}

	handleUnknown(user, cmd);
	return false;
}

bool CommandHandler::dispatchCommand(const std::string &cmd, User &user, UserManager &users, std::istringstream &iss, std::string &disconnectReason) const
{
	if (cmd == "PASS")
	{
		return handlePass(user, iss);
	}
	if (cmd == "NICK")
	{
		return handleNick(user, users, iss);
	}
	if (cmd == "USER")
	{
		return handleUser(user, iss);
	}
	if (cmd == "PING")
	{
		return handlePing(user, iss);
	}
	if (cmd == "QUIT")
	{
		return handleQuit(disconnectReason);
	}
	return false;
}

void CommandHandler::handleUnknown(User &user, const std::string &cmd) const
{
	sendRaw(user.fd, ":ft_irc NOTICE * :Unknown command in starter: " + cmd + "\\r\\n");
}

std::string CommandHandler::trimCrlf(const std::string &s)
{
	std::string out = s;
	while (!out.empty() && (out[out.size() - 1] == '\r' || out[out.size() - 1] == '\n'))
	{
		out.erase(out.size() - 1);
	}
	return out;
}

std::string CommandHandler::upper(const std::string &s)
{
	std::string out = s;
	std::transform(out.begin(), out.end(), out.begin(), ::toupper);
	return out;
}

bool CommandHandler::isRegistrationComplete(const User &user)
{
	return user.passOk && !user.nickname.empty() && !user.username.empty();
}

void CommandHandler::maybeSendWelcome(User &user) const
{
	if (user.welcomed || !isRegistrationComplete(user))
	{
		return;
	}

	user.welcomed = true;
	sendNumeric(user.fd, "001", user.nickname + " :Welcome to ft_irc starter");
	sendRaw(user.fd, ":ft_irc NOTICE " + user.nickname + " :You are registered.\\r\\n");
}

void CommandHandler::sendRaw(int fd, const std::string &message) const
{
	if (send(fd, message.c_str(), message.size(), 0) < 0)
	{
		std::cerr << "send failed on fd=" << fd << ": " << std::strerror(errno) << std::endl;
	}
}

void CommandHandler::sendNumeric(int fd, const std::string &code, const std::string &text) const
{
	sendRaw(fd, ":ft_irc " + code + " * " + text + "\\r\\n");
}
