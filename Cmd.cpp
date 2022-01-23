#include "Server.hpp"
#include "Cmd.hpp"


Command::Command(const Message & msg, User * user, std::vector<User *> & users, std::vector<Channel *> & channels) 
: _msg(msg), _user(user), _users(users), _channels(channels), commandGiveResponse(false) {

	_command["PASS"] = &Command::cmdPass;
	// _command["NICK"] = &Command::cmdNick;
	_command["USER"]= &Command::cmdUser;
	if (user->getRegistered() < 3 && (msg.getCmd() == "PASS" || msg.getCmd() == "NICK" || msg.getCmd() == "USER")) {
		if (msg.getCmd() == "PASS" && user->getfPass() == 0)
			user->setfPass(1);
		else if (msg.getCmd() == "NICK" && user->getfNick() == 0)
			user->setfNick(1);
		else if (msg.getCmd() == "USER" && user->getfUser() == 0)
			user->setfUser(1);
		user->setRegistered(1);
		std::cout << "Registr: " << user->getRegistered() << std::endl;
	}
	(this->*(_command.at(msg.getCmd())))();
	
}

void Command::cmdPass()
{
	std::string password = _msg.getParams().front();
    if (!_user->IsTrueLength(password))
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (_user->isAlreadyRegistered())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ALREADYREGISTRED);
	_user->setPassword(password);
}

void Command::cmdUser()
{
	std::string realname = _msg.getTrailing();

	if (_msg.getParams().size() != 3 || realname.length() == 1)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (_user->isAlreadyRegistered())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ALREADYREGISTRED);
	_user->setUserName(_msg.getParams()[0]);
	_user->setUserRealName(_msg.getTrailing().erase(0, 1));
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

std::pair<std::vector<std::string>, std::string> Command::getResponseForComand() const
{
	return _response;
}

void Command::cmdMode()
{
	
}
