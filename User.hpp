#pragma once

#include <iostream>
#include "Errors.hpp"
#include "Message.hpp"
#include "Server.hpp"

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

    std::string getNickName()const;
    bool isActiveUser()const;
    void setActiveUser(bool active);
};