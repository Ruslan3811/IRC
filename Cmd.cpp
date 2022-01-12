#include "Server.hpp"
#include "Errors.hpp"

int Server::passCmd(Message &msg, User &user)
{
	std::string password = msg.getParams().front();
    if (!user.IsTrueLenPassword(password))
		sendErr(msg, user);
	else if (user.isAlreadyRegistered())
		sendErr(msg, user);
	else
		user.setPassword(password);
	return (0);
}