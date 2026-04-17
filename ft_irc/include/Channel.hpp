#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <set>
#include <string>

class Channel
{
public:
	Channel();
	explicit Channel(const std::string &name);

	const std::string &name() const;
	bool hasMember(int fd) const;
	void addMember(int fd);
	void removeMember(int fd);
	bool empty() const;

private:
	std::string _name;
	std::set<int> _memberFds;
};

#endif
