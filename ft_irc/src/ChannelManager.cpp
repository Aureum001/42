#include "ChannelManager.hpp"

bool ChannelManager::has(const std::string &name) const
{
	return _channels.find(name) != _channels.end();
}

Channel *ChannelManager::get(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it == _channels.end())
	{
		return NULL;
	}
	return &it->second;
}

const Channel *ChannelManager::get(const std::string &name) const
{
	std::map<std::string, Channel>::const_iterator it = _channels.find(name);
	if (it == _channels.end())
	{
		return NULL;
	}
	return &it->second;
}

Channel &ChannelManager::getOrCreate(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it == _channels.end())
	{
		it = _channels.insert(std::make_pair(name, Channel(name))).first;
	}
	return it->second;
}

void ChannelManager::removeIfEmpty(const std::string &name)
{
	std::map<std::string, Channel>::iterator it = _channels.find(name);
	if (it == _channels.end())
	{
		return;
	}
	if (it->second.empty())
	{
		_channels.erase(it);
	}
}
