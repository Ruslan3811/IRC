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
    std::string _hostname;
    std::string _servername;
    std::string _realname;
    int         _flag;
    bool        _active;
	bool		_registered;
	std::vector<std::string> _message;
	int			_fNick;
	int			_fUser;
	int			_fPass;
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

	bool getRegistered() const;
    std::string getRealName()const;
    std::string getPassword()const;
    std::string getNickName()const;
    std::string getUserName()const;
	std::vector<std::string> getMessage() const;

	void setRegistered(bool registered);
    void setUserName(std::string username);
    void setNickName(std::string nickname);
    void setUserRealName(std::string realname);


    bool isActiveUser()const;
    void setActiveUser(bool active);
};