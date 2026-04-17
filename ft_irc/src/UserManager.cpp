#include "UserManager.hpp"

std::map<int, User> &UserManager::all()
{
	return _users;
}

const std::map<int, User> &UserManager::all() const
{
	return _users;
}

void UserManager::add(int fd, const std::string &ip)
{
	User user(fd, ip);
	_users[fd] = user;
}

void UserManager::remove(int fd)
{
	_users.erase(fd);
}

bool UserManager::has(int fd) const
{
	return _users.find(fd) != _users.end();
}

User *UserManager::get(int fd)
{
	std::map<int, User>::iterator it = _users.find(fd);
	if (it == _users.end())
	{
		return NULL;
	}
	return &it->second;
}

const User *UserManager::get(int fd) const
{
	std::map<int, User>::const_iterator it = _users.find(fd);
	if (it == _users.end())
	{
		return NULL;
	}
	return &it->second;
}

bool UserManager::isNicknameInUse(const std::string &nick, int exceptFd) const
{
	std::map<int, User>::const_iterator it = _users.begin();
	for (; it != _users.end(); ++it)
	{
		if (it->first == exceptFd)
		{
			continue;
		}
		if (it->second.nickname == nick)
		{
			return true;
		}
	}
	return false;
}