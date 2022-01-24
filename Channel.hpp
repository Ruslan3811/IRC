#pragma once
#include <string>
#include <vector>

class Channel
{
private:
    std::string                 _channelName;
    std::size_t                 _countUser;
    std::string                 _pass;
    std::vector<std::string>    _banListVec;
    std::vector<std::string>    _inviteListVec;
    std::vector<std::string>    _usersVec;

public:
    Channel(const std::string & channelName);
    Channel(const std::string & channelName, const std::string & channelPass);
    ~Channel();

    std::string     getChannelName() const;
    std::size_t     getCountUser() const;
    std::string     getPass() const;
	std::vector<std::string> &getBanListVec();
	std::vector<std::string> &getInviteListVec();
	std::vector<std::string> &getUserInChannel();

	void	setChannelName(const std::string & channelName);
	void	setCountUser(const std::size_t & countUser);
	void	setPass(const std::string & pass);
    void	pushBanListVec(const std::string & nickname);
	void	pushInviteListVec(const std::string & nickname);
    void	pushUserInChannel(const std::string & nickName);
};
