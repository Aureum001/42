#include "CommandHandler.hpp"
#include "ErrorReplies.hpp"

#include <sstream>

bool CommandHandler::handleUser(User &user, std::istringstream &iss) const
{
	iss >> user.username;
	if (user.username.empty())
	{
		sendRaw(user.fd, ErrorReplies::needMoreParams("USER"));
		return true;
	}

	maybeSendWelcome(user);
	return true;
}
