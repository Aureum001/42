#include "Server.hpp"

#include <cerrno>
#include <cstdlib>
#include <iostream>

namespace
{
volatile sig_atomic_t gStopFlag = 0;

void onSignal(int)
{
	gStopFlag = 1;
}

bool parsePort(const std::string &raw, int &port)
{
	char *end = NULL;
	long value = std::strtol(raw.c_str(), &end, 10);

	if (*raw.c_str() == '\0' || *end != '\0')
	{
		return false;
	}
	if (value < 1024 || value > 65535)
	{
		return false;
	}
	port = static_cast<int>(value);
	return true;
}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}

	int port = 0;
	if (!parsePort(argv[1], port))
	{
		std::cerr << "Error: port must be a number between 1024 and 65535." << std::endl;
		return 1;
	}

	std::signal(SIGINT, onSignal);
	std::signal(SIGTERM, onSignal);

	try
	{
		Server server(port, argv[2]);
		server.run(gStopFlag);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
