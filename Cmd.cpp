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


//доделать изменение ника

//нужна функция определяющая в сети пользователь или нет
int Server::cmdNick(Message &msg, User &user)
{
    std::vector<User *>::iterator begin = this->getUsers().begin();
	std::vector<User *>::iterator end = this->getUsers().end();
    std::string nickname = "";
    if (msg.getParams().size())
    {
        if (user.getNickName().length() > 0)
        { 
            std::cout << "this user already has got nickname";
            return (0);
        }
        for (;begin != end;++begin)
        {
            // std::cout << msg.getParams().front();
            if (msg.getParams().front() == (*begin)->getNickName() && (*begin)->isActiveUser())
            {
                std::cout << "ERR_NICKNAMEINUSE" << std::endl;
                return (0);
                // return sendErr(msg, user,  ERR_NICKNAMEINUSE);
            }
        }
        nickname = msg.getParams().front();
    }
    else if (msg.getTrailing().length() == 0 && msg.getParams().front().length() == 0)
    {
        std::cout << "ERR_NONICKNAMEGIVEN" << std::endl;
        return (0);
    }


    for (size_t c = 0;  c < nickname.length(); ++c)
    {
        if (nickname[c] != ' ' && (nickname[c] < '0' || nickname[c] > '9') && (nickname[c] < 'a' || nickname[c] > 'z') && (nickname[c] < 'A' || nickname[c] > 'Z'))
        {
            std::cout << "ERR_ERRONEUSNICKNAME" << std::endl;
            return (0);
            // return sendErr(msg, user, ERR_ERRONEUSNICKNAME);
        }    
    }

    std::string trailing = msg.getTrailing();
    
    if (msg.getTrailing().length() > 0 && nickname.length() == 0)
    {
        trailing.erase(0, 1);
        std::string old_nick = trailing.substr(0, trailing.find(" "));
        trailing.erase(0, trailing.find(" "));
        int i = 0;
        for (; trailing[i] == ' '; ++i){}
        trailing.erase(0, i);
        i = 0;
        for (; trailing[i] != ' ' && trailing[i]; ++i){}
        std::string nick = trailing.substr(0, i);
        trailing.erase(0, i);
        i = 0;
        for (; trailing[i] == ' '; ++i){}
        trailing.erase(0, i);
        nickname = trailing;    
    }
    user.setUserName(nickname);
	return (0);
}