#include "Exception.hpp"

enum ERRORS
{
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    ERR_NICKCOLLISION = 436,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
};

std::string errorRequest::_getErrorMessage(int codeError)
{
	switch (codeError)
	{
		case ERR_NEEDMOREPARAMS:
			return "You may not reregister\n";
		case ERR_ALREADYREGISTRED:
			return _msg + " :Not enough parameters\n";
		case ERR_NONICKNAMEGIVEN:
			return " :No nickname given\n";
		case ERR_ERRONEUSNICKNAME:
			return _user + " :Erroneus nickname\n";
		case ERR_NICKNAMEINUSE:
			return _user + " :Nickname is already in use\n";
		case ERR_NICKCOLLISION:
			return _user + " :Nickname is already in use\n";
	}
	return "type error not found";
}
