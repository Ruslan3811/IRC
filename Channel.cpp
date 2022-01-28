#include "Channel.hpp"

// Constructors and destructor

Channel::Channel(const std::string & channelName) 
:  _channelName(channelName), _countUser(300), _onlyInvaite(false), _hasPass(false), _secretChannel(false), \
 _privateChannel(false), _moderChannel(false)
{
    _topicChannel = "No topic is set";
}

Channel::Channel(const std::string & channelName, const std::string & channelPass,const std::string & userName) 
: _channelName(channelName), _pass(channelPass), _userHostNick(userName), _onlyInvaite(false), _hasPass(false), _secretChannel(false), _privateChannel(false), _moderChannel(false)  {}

Channel::~Channel() {}

// Getters
bool                    Channel::getHasPass() const {return _hasPass; }

bool                    Channel::getOnlyInvaite() const {return _onlyInvaite; };

std::string Channel::getChannelName() const { return _channelName; }

std::size_t     Channel::getCountUser() const { return _usersVec.size(); }
std::size_t     Channel::getCountUserCanJoin() const { return _countUser; }

std::string     Channel::getPass() const { return _pass; }

std::vector<std::string> &Channel::getBanListVec() { return _banListVec; }

std::vector<std::string> &Channel::getInviteListVec() { return _inviteListVec; }

std::vector<std::pair<std::string, int > > &Channel::getUserInChannel() { return _usersVec; }

// Setters

void                    Channel::setOnlyInvaite(bool b) { _onlyInvaite = b; }

void                    Channel::setHasPass(bool b) { _hasPass = b; }
void	Channel::setChannelName(const std::string & channelName) { _channelName = channelName; }

void	Channel::setCountUser(std::size_t countUser) { _countUser = countUser; }

void	Channel::setPass(const std::string & pass) { _pass = pass; }

void	Channel::pushBanListVec(const std::string & nickname) { _banListVec.push_back(nickname); }

void	Channel::pushInviteListVec(const std::string & nickname) { _inviteListVec.push_back(nickname); }

void	Channel::pushUserInChannel(const std::string & nickName, int soket) { _usersVec.push_back(std::make_pair(nickName, soket)); }

void    Channel::setHostName(const std::string &hostname)
{
    _userHostNick = hostname;
}

void    Channel::setPrivateChannel(bool b)
{
    _privateChannel = b;
}

void    Channel::setSecretChannel(bool b)
{
    _secretChannel = b;
}

void    Channel::setModerChannel(bool b)
{
    _moderChannel = b;
}

std::string Channel::getBanMask() const
{
    return _banMask;
}

void    Channel::setBanMask(const std::string &mask)
{
    _banMask = mask;
}

std::string     Channel::getHostName() const
{
    return _userHostNick;
}

bool    Channel::isPrivateChannel() const
{
    return _privateChannel;
}

void                    Channel::eraseUserForInvaiteList(const std::string & name)
{
    std::vector<std::string>::iterator it = std::find(_inviteListVec.begin(), _inviteListVec.end(), name);
    if (it != _inviteListVec.end())
        _inviteListVec.erase(it);
}

void                    Channel::eraseUserForChannel(const std::string & name, int id)
{
    std::vector<std::pair<std::string, int> >::iterator it = std::find(_usersVec.begin(), _usersVec.end(), std::make_pair(name, id));
    if (it != _usersVec.end())
        _usersVec.erase(it);
}

bool                    Channel::isSecretChannel() const
{
    return _secretChannel;
}