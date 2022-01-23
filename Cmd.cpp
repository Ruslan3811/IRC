#include "Server.hpp"
#include "cmd.hpp"


Command::Command(const Message & msg, User * user, std::vector<User *> & users, std::vector<Channel *> & channels) 
: _msg(msg), _user(user), _users(users), _channels(channels), commandGiveResponse(false) {

	_command["PASS"] = &Command::cmdPass;
	_command["NICK"] = &Command::cmdNick;
	_command["USER"]= &Command::cmdUser;
	if (user->getRegistered() < 3 && (msg.getCmd() == "PASS" || msg.getCmd() == "NICK" || msg.getCmd() == "USER")) {
		user->setRegistered(1);
		std::cout << "Registr: " << user->getRegistered() << std::endl;
	}
	(this->*(_command.at(msg.getCmd())))();
	
}

void Command::cmdPass()
{
    if (!_msg.getParams().size())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (_user->isAlreadyRegistered())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ALREADYREGISTRED);
	_user->setPassword(_msg.getParams().front());
}

void Command::cmdUser()
{
	std::string realname = _msg.getTrailing();
	if (_msg.getParams().size() != 3 || realname.length() == 1)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (_user->isAlreadyRegistered())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ALREADYREGISTRED);
	_user->setUserName(_msg.getParams().front());
	_user->setUserRealName(_msg.getTrailing().erase(0, 1));
}

void Command::cmdNick()
{
	if (_user->getNickName().length() > 0 && _msg.getPrefix().length() == 0)
	{
		std::cout << "You've already registered your name\n";
		return ;
	}
	if (_msg.getParams().size() == 0)
	{
		if (_user->getNickName().length() == 0)
			throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NONICKNAMEGIVEN);
	}
	std::string nickname = _msg.getParams().front();
	for (size_t c = 0;  c < _msg.getParams().front().length(); ++c)
    {
        if (nickname[c] != ' ' && (nickname[c] < '0' || nickname[c] > '9') && (nickname[c] < 'a' || nickname[c] > 'z') && (nickname[c] < 'A' || nickname[c] > 'Z'))
			throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ERRONEUSNICKNAME);
	}

	std::vector<User *>::iterator begin = _users.begin();
	std::vector<User *>::iterator end = _users.end();
	for (;begin != end; ++begin)
	{
		if (nickname == (*begin)->getNickName() && (*begin)->isActiveUser())
			throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NICKNAMEINUSE);
	}
	_user->setUserName(nickname);
}

//chanel command

void Command::PrintMsg()
{
	std::vector<std::string> param = _msg.getParams();
	std::vector<std::pair<std::string, bool> > userAndChanel;
	std::string	messegeFromUser = _msg.getTrailing();
	if (param.size() < 1)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	for (size_t i = 0; i < param.size(); ++i)
	{
		bool userExist = false;
		for (size_t j = 0; j < _users.size(); ++j)
		{
			if (_users[j]->getNickName() == param[i])
			{
				userAndChanel.push_back(std::make_pair(param[i], true));
				userExist = true;
				break;
			}
		}
		for (size_t j = 0; j < _channels.size(); ++j)
		{
			if (_channels[j]->getChannelName() == param[i])
			{
				userAndChanel.push_back(std::make_pair(param[i], false));
				userExist = true;
				break;
			}
		}
		if (userExist == false && i == 0)
		{
			throw errorRequest(param[i], _user->getNickName(), ERR_NOSUCHNICK);
		}
		else if (userExist == false)
		{
			messegeFromUser = param[i];
			break;
		}
	}
	for (size_t i = 0; i < userAndChanel.size(); ++i)
	{
		if (userAndChanel[i].second == true)
		{
			for (size_t j = 0; j < _users.size(); ++j)	
			{
				if (_users[j]->getNickName() == userAndChanel[i].first)
				{
					send(_users[j]->getSocket(), messegeFromUser.c_str(), messegeFromUser.size(), IRC_NOSIGNAL);
				}
			}
		}
	}
}

