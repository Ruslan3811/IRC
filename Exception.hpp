#pragma once
#include <exception>
#include <string>
class errorRequest : public std::exception
{
    private:
    std::string _msg;
    std::string _user;
    std::string _errorMessege;
    public:
    errorRequest(const std::string & msg, int codeError) : _msg(msg), _user(msg)
    {
        _errorMessege = _getErrorMessage(codeError);
    }
    errorRequest(const std::string & msg, const std::string & user, int codeError) : _msg(msg),  _user(user)
    {
        _errorMessege = _getErrorMessage(codeError);
    }
    virtual const char* what() const throw ()
    {
        return _errorMessege.c_str();
    }
    virtual ~errorRequest() throw() {}
    private:
    std::string _getErrorMessage(int codeError);
};