#include "Channel.hpp"

// Constructors and destructor

Channel::Channel(const std::string & channelName) : _channelName(channelName)
{
    
}

Channel::Channel(const std::string & channelName, const std::string & channelPass,const std::string & userName) 
: _channelName(channelName), _pass(channelPass), _userHostNick(userName), _onlyInvaite(false), _hasPass(false) {}

Channel::~Channel() {}

// Getters
bool                    Channel::getHasPass() const {return _hasPass; }

bool                    Channel::getOnlyInvaite() const {return _onlyInvaite; };

std::string Channel::getChannelName() const { return _channelName; }

std::size_t     Channel::getCountUser() const { return _countUser; }

std::string     Channel::getPass() const { return _pass; }

std::vector<std::string> &Channel::getBanListVec() { return _banListVec; }

std::vector<std::string> &Channel::getInviteListVec() { return _inviteListVec; }

std::vector<std::pair<std::string, int > > &Channel::getUserInChannel() { return _usersVec; }

// Setters

void                    Channel::setOnlyInvaite(bool b) { _hasPass = b; }
void                    Channel::setHasPass(bool b) { _hasPass = b; }
void	Channel::setChannelName(const std::string & channelName) { _channelName = channelName; }

void	Channel::setCountUser(const std::size_t & countUser) { _countUser = countUser; }

void	Channel::setPass(const std::string & pass) { _pass = pass; }

void	Channel::pushBanListVec(const std::string & nickname) { _banListVec.push_back(nickname); }

void	Channel::pushInviteListVec(const std::string & nickname) { _inviteListVec.push_back(nickname); }

void	Channel::pushUserInChannel(const std::string & nickName, int soket) { _usersVec.push_back(std::make_pair(nickName, soket)); }
