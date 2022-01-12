#include "Server.hpp"

User::User(int socket, std::string host, std::string name): _socket(socket), _host(host), _name(name){}

User::User(void): _flag(0){}

User::~User(void){}

void User::setSocket(int sock)
{
    _socket = sock;
}

int User::getFlag()const
{
    return _flag;
}

int User::IsTrueLenPassword(std::string password)
{
    if (!password.length())
        return false;
    return true;
}

bool User::isAlreadyRegistered(void)const
{
    if (getFlag() == ERR_ALREADYREGISTRED)
        return true;
    return false;
}

void User::setFlag(int flag)
{
    _flag = flag;
}

void User::setPassword(std::string password)
{
    _password = password;
}

int User::getSocket()const
{
    return _socket;
}
