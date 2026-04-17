#include "Channel.hpp"

Channel::Channel()
	: _name("")
{
}

Channel::Channel(const std::string &name)
	: _name(name)
{
}

const std::string &Channel::name() const
{
	return _name;
}

bool Channel::hasMember(int fd) const
{
	return _memberFds.find(fd) != _memberFds.end();
}

void Channel::addMember(int fd)
{
	_memberFds.insert(fd);
}

void Channel::removeMember(int fd)
{
	_memberFds.erase(fd);
}

bool Channel::empty() const
{
	return _memberFds.empty();
}
