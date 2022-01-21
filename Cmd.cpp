#include "Server.hpp"
#include "Errors.hpp"
//доделать
int Server::Connection(User &user)
{
	if (user.IsTrueLength(user.getNickName()) > 0 && user.IsTrueLength(user.getRealName()) > 0)
	{
		if (user.IsTrueLength(_password) == 0 || user.getPassword() == _password)
		{
			// if (!(user.getRegistered() == 3))
			// {
			// 	user.setFlag();
			// }
		}
		else
			return (-1);
	}
	else
		return (0);
}

int Server::cmdPass(Message &msg, User &user)
{
	std::string password = msg.getParams().front();
    if (!user.IsTrueLength(password))
		return sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		return sendErr(msg, user, ERR_ALREADYREGISTRED);
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


//доделать изменение ника

int Server::cmdNick(Message &msg, User &user)
{
	std::string nickname = msg.getParams().front();

	if (nickname.length() == 0)
	{
		if (user.getNickName().length() == 0)
			sendErr(msg, user, ERR_NONICKNAMEGIVEN);
	}

	for (size_t c = 0;  c < msg.getParams().front().length(); ++c)
    {
        if (nickname[c] != ' ' && (nickname[c] < '0' || nickname[c] > '9') && (nickname[c] < 'a' || nickname[c] > 'z') && (nickname[c] < 'A' || nickname[c] > 'Z'))
            sendErr(msg, user, ERR_ERRONEUSNICKNAME);
	}

	std::vector<User *>::iterator begin = this->getUsers().begin();
	std::vector<User *>::iterator end = this->getUsers().end();
	for (;begin != end; ++begin)
	{
		if (nickname == (*begin)->getNickName() && (*begin)->isActiveUser())
			sendErr(msg, user,  ERR_NICKNAMEINUSE);
	}
	if (':' + user.getNickName() ==  nickname or msg.getPrefix().length() == 0)
		user.setUserName(nickname);
	return (0);
}

