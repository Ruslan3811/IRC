#include "Server.hpp"
#include "Errors.hpp"

int Server::cmdPass(Message &msg, User &user)
{
	std::string password = msg.getParams().front();
    if (!user.IsTrueLength(password))
		sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		sendErr(msg, user, ERR_ALREADYREGISTRED);
	else
		user.setPassword(password);
	return (0);
}

int Server::cmdUser(Message &msg, User &user)
{
	std::string username = msg.getParams().front();
	std::string trailing = msg.getTrailing();
	if ((!user.IsTrueLength(username) && msg.getParams().size() != 3) || user.IsTrueLength(trailing) == 1)
		sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		sendErr(msg, user, ERR_ALREADYREGISTRED);
	// else
	// 	user.setUserName();
	return (0);
}