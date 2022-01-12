#pragma once

#include <iostream>
#include "Errors.hpp"
#include "Message.hpp"

class User
{
private:
    int _socket;
    std::string _host;
    std::string _name;
    int _flag;
    std::string _password;

public:
    User(void);
    ~User(void);

    User(int _socket, std::string _host, std::string _name);

    bool isAlreadyRegistered(void)const;
    void setFlag(int flag);

    void setPassword(std::string password);
    int IsTrueLenPassword(std::string password);

    int getSocket()const;
    void setSocket(int sock);

    int getFlag()const;
};