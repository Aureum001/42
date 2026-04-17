#include "CommandHandler.hpp"
#include "ErrorReplies.hpp"

#include <sstream>

bool CommandHandler::handleNick(User &user, UserManager &users, std::istringstream &iss) const
{
	std::string nick;
	iss >> nick;
	if (nick.empty())
	{
		sendRaw(user.fd, ErrorReplies::noNicknameGiven());
		return true;
	}
	if (users.isNicknameInUse(nick, user.fd))
	{
		sendRaw(user.fd, ErrorReplies::nicknameInUse(nick));
		return true;
	}

	user.nickname = nick;
	maybeSendWelcome(user);
	return true;
}
