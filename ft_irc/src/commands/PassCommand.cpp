#include "CommandHandler.hpp"
#include "ErrorReplies.hpp"

#include <sstream>

bool CommandHandler::handlePass(User &user, std::istringstream &iss) const
{
	std::string pass;
	iss >> pass;
	if (pass.empty())
	{
		sendRaw(user.fd, ErrorReplies::needMoreParams("PASS"));
		return true;
	}
	if (pass != _password)
	{
		sendRaw(user.fd, ErrorReplies::passwordIncorrect());
		return true;
	}

	user.passOk = true;
	sendRaw(user.fd, ":ft_irc NOTICE AUTH :Password accepted\\r\\n");
	maybeSendWelcome(user);
	return true;
}
