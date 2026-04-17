#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "User.hpp"

#include <map>
#include <string>

class UserManager
{
public:
	std::map<int, User> &all();
	const std::map<int, User> &all() const;

	void add(int fd, const std::string &ip);
	void remove(int fd);

	bool has(int fd) const;
	User *get(int fd);
	const User *get(int fd) const;

	bool isNicknameInUse(const std::string &nick, int exceptFd) const;

private:
	std::map<int, User> _users;
};

#endif