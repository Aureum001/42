#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "UserManager.hpp"

#include <sstream>
#include <string>

class CommandHandler
{
public:
	explicit CommandHandler(const std::string &password);

	bool handleLine(User &user, UserManager &users, const std::string &line, std::string &disconnectReason) const;
	static std::string trimCrlf(const std::string &s);

private:
	std::string _password;

	bool dispatchCommand(const std::string &cmd, User &user, UserManager &users, std::istringstream &iss, std::string &disconnectReason) const;
	bool handlePass(User &user, std::istringstream &iss) const;
	bool handleNick(User &user, UserManager &users, std::istringstream &iss) const;
	bool handleUser(User &user, std::istringstream &iss) const;
	bool handlePing(User &user, std::istringstream &iss) const;
	bool handleQuit(std::string &disconnectReason) const;
	void handleUnknown(User &user, const std::string &cmd) const;

	static std::string upper(const std::string &s);
	static bool isRegistrationComplete(const User &user);

	void maybeSendWelcome(User &user) const;
	void sendRaw(int fd, const std::string &message) const;
	void sendNumeric(int fd, const std::string &code, const std::string &text) const;
};

#endif
