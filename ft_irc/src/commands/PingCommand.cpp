#include "CommandHandler.hpp"

#include <sstream>

bool CommandHandler::handlePing(User &user, std::istringstream &iss) const
{
	std::string payload;
	std::getline(iss, payload);
	payload = trimCrlf(payload);
	sendRaw(user.fd, "PONG" + payload + "\\r\\n");
	return true;
}
