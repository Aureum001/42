#include "ErrorReplies.hpp"

std::string ErrorReplies::notRegistered()
{
	return ":ft_irc 451 * :You have not registered\\r\\n";
}

std::string ErrorReplies::needMoreParams(const std::string &command)
{
	return ":ft_irc 461 * " + command + " :Not enough parameters\\r\\n";
}

std::string ErrorReplies::noNicknameGiven()
{
	return ":ft_irc 431 * :No nickname given\\r\\n";
}

std::string ErrorReplies::nicknameInUse(const std::string &nick)
{
	return ":ft_irc 433 * " + nick + " :Nickname is already in use\\r\\n";
}

std::string ErrorReplies::passwordIncorrect()
{
	return ":ft_irc 464 * :Password incorrect\\r\\n";
}
