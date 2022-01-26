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
    std::vector<std::pair <std::string, int> >    _usersVec;
    std::string                 _userHostNick;
    std::string                 _topicChannel;

    bool                        _onlyInvaite;
    bool                        _hasPass;
    bool                        _secretChannel;
    bool                        _privateChannel;
    bool                        _moderChannel;
    std::string                 _banMask;

public:
    Channel(const std::string & channelName);
    Channel(const std::string & channelName, const std::string & channelPass, const std::string & userName);
    ~Channel();

    std::string                 getChannelName() const;
    std::size_t                 getCountUser() const;
    std::string                 getPass() const;
    std::string                 getBanMask() const;
	std::vector<std::string> &getBanListVec();
	std::vector<std::string> &getInviteListVec();
	std::vector<std::pair<std::string, int > > &getUserInChannel();
    bool                    getHasPass() const;
    bool                    getOnlyInvaite() const;
    std::string             getHostName() const;
    std::string             getTopicChannel() const;
    bool                    getModerChannel() const;

    void                    setOnlyInvaite(bool);
    void                    setHasPass(bool);
    void                    setTopicChannel(const std::string & topic);
    void    setBanMask(const std::string & banMask);
    void    setModerChannel(bool);
    void    setSecretChannel(bool);
    void    setPrivateChannel(bool);
    void    setHostName(const std::string & name);
	void	setChannelName(const std::string & channelName);
	void	setCountUser(std::size_t countUser);
	void	setPass(const std::string & pass);
    void	pushBanListVec(const std::string & nickname);
	void	pushInviteListVec(const std::string & nickname);
    void	pushUserInChannel(const std::string & nickName, int soket);
};
