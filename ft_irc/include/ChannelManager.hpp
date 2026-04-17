#ifndef CHANNELMANAGER_HPP
#define CHANNELMANAGER_HPP

#include "Channel.hpp"

#include <map>
#include <string>

class ChannelManager
{
public:
	bool has(const std::string &name) const;
	Channel *get(const std::string &name);
	const Channel *get(const std::string &name) const;
	Channel &getOrCreate(const std::string &name);
	void removeIfEmpty(const std::string &name);

private:
	std::map<std::string, Channel> _channels;
};

#endif
