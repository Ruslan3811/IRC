#pragma once
#include <exception>
#include "Message.hpp"
#include "User.hpp"

class errorRequest : public std::exception
{
    private:
    Message _msg;
    User    _user;
    std::string _errorMessege;
    public:
	virtual ~errorRequest() _NOEXCEPT;
    errorRequest(const Message & msg,const User & user, int codeError) : _msg(msg),  _user(user)
    {
        _errorMessege = _getErrorMessage(codeError);
    }
   const char * what() const throw();
    private:
    std::string _getErrorMessage(int codeError);
};