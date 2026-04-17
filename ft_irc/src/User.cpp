#include "User.hpp"

User::User()
	: fd(-1), passOk(false), welcomed(false)
{
}

User::User(int userFd, const std::string &userIp)
	: fd(userFd), ip(userIp), passOk(false), welcomed(false)
{
}

User::User(const User &other)
	: fd(other.fd),
	  ip(other.ip),
	  passOk(other.passOk),
	  welcomed(other.welcomed),
	  nickname(other.nickname),
	  username(other.username),
	  recvBuffer(other.recvBuffer)
{
}

User &User::operator=(const User &other)
{
	if (this != &other)
	{
		fd = other.fd;
		ip = other.ip;
		passOk = other.passOk;
		welcomed = other.welcomed;
		nickname = other.nickname;
		username = other.username;
		recvBuffer = other.recvBuffer;
	}
	return *this;
}

User::~User()
{
}
