#include "Server.hpp"
#include "Errors.hpp"

int Server::cmdPass(Message &msg, User &user)
{
	std::string password = msg.getParams().front();
    if (!user.IsTrueLength(password))
		sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		sendErr(msg, user, ERR_ALREADYREGISTRED);
	user.setPassword(password);
	return (0);
}

int Server::cmdUser(Message &msg, User &user)
{
	std::string realname = msg.getTrailing();

	if (msg.getParams().size() != 3 || realname.length() == 1)
		sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		sendErr(msg, user, ERR_ALREADYREGISTRED);
	user.setUserName(msg.getParams()[0]);
	user.setUserRealName(msg.getTrailing().erase(0, 1));
	this->setHostName(msg.getParams()[1]);
	this->setServerName(msg.getParams()[2]);
	return (0);
}

int Server::cmdNick(Message &msg, User &user)
{
  	std::vector<User *>::iterator begin = this->getUsers().begin();
	std::vector<User *>::iterator end = this->getUsers().end();

	for (; begin != end; ++begin)
	{
		if (user.getNickName() == (*begin)->getNickName())
			std::cout << 1;
		else
			std::cout << 2;
	}
	std::cout << msg.getCmd();
	return (0);
}

void get()
{}