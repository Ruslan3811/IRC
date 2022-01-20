#pragma once
#include <exception>
#include "Message.hpp"
#include "User.hpp"

enum ERRORS
{
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    ERR_NICKCOLLISION = 436,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
};
class errorRequest : public std::exception
{
    private:
    Message _msg;
    User    _user;
    std::string _errorMessege;
    public:
    errorRequest(const Message & msg,const User & user, int codeError) : _msg(msg),  _user(user)
    {
        _errorMessege = _getErrorMessage(codeError);
    }
    void what() noexcept;
    private:
    std::string _getErrorMessage(int codeError);
};