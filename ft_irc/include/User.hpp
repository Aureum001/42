#ifndef USER_HPP
#define USER_HPP

#include <string>

class User
{
public:
	int fd;
	std::string ip;
	bool passOk;
	bool welcomed;
	std::string nickname;
	std::string username;
	std::string recvBuffer;

	User();
	User(int fd, const std::string &ip);
	User(const User &other);
	User &operator=(const User &other);
	~User();
};

#endif
