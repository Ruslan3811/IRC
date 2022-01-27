#pragma once

#include <iostream>
#include "Message.hpp"
#include "CodeError.hpp"
class User
{
private:
    int         _socket;
    std::string _host;
    std::string _password;
    std::string _nickname;
    std::string _username;
    std::string _servername;
    std::string _realname;
    int         _flag;
    bool        _active;
	bool		_registered;
	std::vector<std::string> _message;
    std::vector<std::string> _channels;
	int			_fNick;
	int			_fUser;
	int			_fPass;
    std::string _away_status;
    int         _awayflag;

public:
    User(void);
    ~User(void);

    User(int socket, std::string host, std::string servername);

    void eraseOneChannel(const std::string & name);

    void eraseAllChannel();
    bool isAlreadyRegistered(void) const;

    std::vector<std::string> & getAllChannel();
    void pushChannelName(const std::string &);

    void setFlag(int flag);

    void setPassword(std::string password);
    int IsTrueLength(std::string str);

    int getSocket()const;

    int getFlag()const;

    // Alena
    int readMsg();

	bool getRegistered() const;
    std::string getHostName()const;
    std::string getPassword()const;
    std::string getNickName()const;
    std::string getUserName()const;
    std::string getServerName()const;
    std::string getRealName()const;
	std::vector<std::string> getMessage() const;

	void setRegistered(bool registered);
    void setUserName(std::string username);
    void setNickName(std::string nickname);
    void setUserRealName(std::string realname);


    bool isActiveUser()const;
    void setActiveUser(bool active);

    void setAwayStatus(std::string msg);
    std::string getAwayStatus()const;
    int getfPass() const;

    void setAwayFlag(int nbr);
    int getAwayFlag()const;
};