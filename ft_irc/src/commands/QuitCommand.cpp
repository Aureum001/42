#include "CommandHandler.hpp"

#include <sstream>

bool CommandHandler::handleQuit(std::string &disconnectReason) const
{
	disconnectReason = "QUIT command";
	return true;
}
