#pragma once

#include <iostream>
#include "Message.hpp"


enum ERRORS
{
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    ERR_NICKCOLLISION = 436,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
};

class User
{
private:
    int         _socket;
    std::string _host;
    std::string _username;
    int         _flag;
    std::string _password;
    std::string _realname;
    bool        _active;
	int			_registered;
	std::vector<std::string> _message;
public:
    User(void);
    ~User(void);

    User(int socket, std::string host);

    bool isAlreadyRegistered(void)const;
    void setFlag(int flag);

    void setPassword(std::string password);
    int IsTrueLength(std::string str);

    int getSocket()const;
    void setSocket(int sock);

    int getFlag()const;

    // Alena
    int readMsg();
	int getRegistered() const;
	void setRegistered(int registered);
	std::vector<std::string> getMessage() const;
    void setUserName(std::string username);
    void setUserRealName(std::string realname);

    std::string getRealName()const;
    std::string getNickName()const;
    bool isActiveUser()const;
    void setActiveUser(bool active);
};