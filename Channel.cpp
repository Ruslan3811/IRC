#include "Channel.hpp"

std::string Channel::getChannelName() const
{
    return _chanelName;
}

Channel::Channel(const std::string & channelName) : _chanelName(channelName)
{
    
}