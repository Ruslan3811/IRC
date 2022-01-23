#pragma once
#include <string>
#include <vector>
class Channel
{
    std::string                 _chanelName;
    std::size_t                 _countUser;
    std::string                 _pass;
    std::vector<std::string>    _banListVec;
    std::vector<std::string>    _inviteListVec;
    std::vector<std::string>    _usersVec;

    public:
    Channel(const std::string & channelName);
    Channel(const std::string & channelName, const std::string & channelPass);


    std::string        getChannelName() const;
    std::string        getPass() const;


    void               pushUserInChannel(const std::string & nickName);
    ~Channel();
};