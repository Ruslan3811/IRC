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

    bool                        _onlyInvaite;
    bool                        _hasPass;


public:
    Channel(const std::string & channelName);
    Channel(const std::string & channelName, const std::string & channelPass, const std::string & userName);
    ~Channel();

    std::string     getChannelName() const;
    std::size_t     getCountUser() const;
    std::string     getPass() const;
	std::vector<std::string> &getBanListVec();
	std::vector<std::string> &getInviteListVec();
	std::vector<std::pair<std::string, int > > &getUserInChannel();
    bool                    getHasPass() const;
    bool                    getOnlyInvaite() const;
    void                    setOnlyInvaite(bool);
    void                    setHasPass(bool);

	void	setChannelName(const std::string & channelName);
	void	setCountUser(const std::size_t & countUser);
	void	setPass(const std::string & pass);
    void	pushBanListVec(const std::string & nickname);
	void	pushInviteListVec(const std::string & nickname);
    void	pushUserInChannel(const std::string & nickName, int soket);

};
