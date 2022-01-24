#include "Channel.hpp"

// Constructors and destructor

Channel::Channel(const std::string & channelName) : _channelName(channelName)
{
    
}

Channel::Channel(const std::string & channelName, const std::string & channelPass) : _channelName(channelName), _pass(channelPass) {}

Channel::~Channel() {}

// Getters

std::string Channel::getChannelName() const { return _channelName; }

std::size_t     Channel::getCountUser() const { return _countUser; }

std::string     Channel::getPass() const { return _pass; }

std::vector<std::string> &Channel::getBanListVec() { return _banListVec; }

std::vector<std::string> &Channel::getInviteListVec() { return _inviteListVec; }

std::vector<std::string> &Channel::getUserInChannel() { return _usersVec; }

// Setters

void	Channel::setChannelName(const std::string & channelName) { _channelName = channelName; }

void	Channel::setCountUser(const std::size_t & countUser) { _countUser = countUser; }

void	Channel::setPass(const std::string & pass) { _pass = pass; }

void	Channel::pushBanListVec(const std::string & nickname) { _banListVec.push_back(nickname); }

void	Channel::pushInviteListVec(const std::string & nickname) { _inviteListVec.push_back(nickname); }

void	Channel::pushUserInChannel(const std::string & nickName) { _usersVec.push_back(nickName); }
