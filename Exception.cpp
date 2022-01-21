#include "Exception.hpp"

std::string errorRequest::_getErrorMessage(int codeError)
{
	switch (codeError)
	{
		case ERR_NEEDMOREPARAMS:
			return "You may not reregister\n";
		case ERR_ALREADYREGISTRED:
			return _msg.getCmd() + " :Not enough parameters\n";
		case ERR_NONICKNAMEGIVEN:
			return ":No nickname given\n";
		case ERR_ERRONEUSNICKNAME:
			return _user.getNickName() + " :Erroneus nickname\n";
		case ERR_NICKNAMEINUSE:
			return _user.getNickName() + " :Nickname is already in use\n";
		case ERR_NICKCOLLISION:
			return _user.getNickName() + " :Nickname is already in use\n";
	}
	return "type error not found";
}
