#include "Server.hpp"
#include "Errors.hpp"

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
		return sendErr(msg, user, ERR_NEEDMOREPARAMS);
	else if (user.isAlreadyRegistered())
		return sendErr(msg, user, ERR_ALREADYREGISTRED);
	user.setUserName(msg.getParams()[0]);
	user.setUserRealName(msg.getTrailing().erase(0, 1));
	this->setHostName(msg.getParams()[1]);
	this->setServerName(msg.getParams()[2]);
	return (0);
}

//нужна функция определяющая в сети пользователь или нет
int Server::cmdNick(Message &msg, User &user)
{
	std::string nickname = msg.getParams().front();
	//msg.params consinsts of 1 arg = NickName
  	std::vector<User *>::iterator begin = this->getUsers().begin();
	std::vector<User *>::iterator end = this->getUsers().end();
	//No nickname given
	if (msg.getParams().size() == 0)
		return sendErr(msg, user,  ERR_NONICKNAMEGIVEN);
	
	for (size_t c = 0;  c < nickname.length(); ++c)
    {
        if ((nickname[c] < '0' || nickname[c] > '9') && (nickname[c] < 'a' || nickname[c] > 'z') && (nickname[c] < 'A' || nickname[c] > 'Z'))
            return sendErr(msg, user, ERR_ERRONEUSNICKNAME);
    }

	for (; begin != end; ++begin)
	{
		if (user.getNickName() == (*begin)->getNickName() && user.isActiveUser())
			return sendErr(msg, user,  ERR_NICKNAMEINUSE);		
	}
	user.setUserName(msg.getParams().front());
	return (0);
}