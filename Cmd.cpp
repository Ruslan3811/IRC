#include "Server.hpp"
#include "Cmd.hpp"

void printNum()
{
	static int i = 0;
	std::cout << ++i << std::endl;
}

void printVectorStr(std::vector<std::string> & vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

Command::Command(const Message & msg, User * user, std::vector<User *> & users, std::vector<Channel *> & channels, std::string servPass) 
: _msg(msg), _user(user), _users(users), _channels(channels), commandGiveResponse(false), _servPass(servPass)
{
	_command["PASS"] = &Command::cmdPass;
	_command["NICK"] = &Command::cmdNick;
	_command["USER"] = &Command::cmdUser;
	_command["PRIVMSG"] = &Command::PrivMsg;
	_command["JOIN"] = &Command::cmdJoin;

	if (user->getRegistered() == false && msg.getCmd() != "PASS" && msg.getCmd() != "NICK" && msg.getCmd() != "USER")
		throw errorRequest(_msg.getCmd(), user->getNickName(), ERR_NOTREGISTERED);

	if (_command.find(msg.getCmd()) == _command.end())
		throw  errorRequest(_msg.getCmd(), _user->getNickName(), ERR_UNKNOWNCOMMAND);
	(this->*(_command.at(msg.getCmd())))();
}

void Command::checkConnection() {
	if (_user->getNickName().size() > 0 && _user->getUserName().size() > 0) {
		if (_servPass.size() == 0 || _user->getPassword() == _servPass) {
			if (_user->getRegistered() == false) {
				_user->setRegistered(true);
				send(_user->getSocket(), "Registration complete!\n", 24, 0);
				// sendMOTD(_user);
			}
		}
		else {
			throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NOTREGISTERED);
		}
	}
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
	if (_msg.getParams().size() != 4 || realname.length() == 1)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (_user->isAlreadyRegistered())
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_ALREADYREGISTRED);
	_user->setUserName(_msg.getParams().front());
	_user->setUserRealName(_msg.getTrailing().erase(0, 1));
	checkConnection();
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
	_user->setNickName(nickname);
	checkConnection();
}

//chanel command

// const unsigned FNV_32_PRIME = 0x01000193;
// const unsigned HVAL_START = 0x811c9dc5;

// unsigned int __hashFile(char * buff, unsigned int hval)
// {
// 	while (*buff)
// 	{
// 		hval ^= (unsigned int)*buff++;
// 		hval *= FNV_32_PRIME;
// 	}
// 	return hval;
// }

void Command::PrivMsg()
{
	std::vector<std::string> param = _msg.getParams();
	std::vector<std::pair<std::string, bool> > userAndChanel;
	std::string	messegeFromUser = _msg.getTrailing() + "\n";
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
		if (userExist)
			continue;
		for (size_t j = 0; j < _channels.size(); ++j)
		{
			if (_channels[j]->getChannelName() == param[i])
			{
				userAndChanel.push_back(std::make_pair(param[i], false));
				userExist = true;
				break;
			}
		}
		if (userExist)
			continue;
		if (userExist == false && i == 0)
		{
			throw errorRequest(param[i], _user->getNickName(), ERR_NOSUCHNICK);
		}
		else if (userExist == false)
		{
			messegeFromUser = param[i] + "\n";
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
					std::string returnMessage = ":" + _user->getNickName();
					send(_users[j]->getSocket(), messegeFromUser.c_str(), messegeFromUser.size(), IRC_NOSIGNAL);
					break;
				}
			}
		}
		if (userAndChanel[i].second == false)
		{
			for (size_t j = 0; j < _channels.size(); ++j)
			{
				if (userAndChanel[i].first == _channels[j]->getChannelName())
				{
					printNum();
					std::vector<std::pair <std::string, int> > vecUserInChannel = _channels[j]->getUserInChannel();
					if (find(vecUserInChannel.begin(), vecUserInChannel.end(), std::make_pair(_user->getNickName(), _user->getSocket()))
					 != vecUserInChannel.end())
					{
						for (size_t k = 0; k < vecUserInChannel.size(); ++k)
						{
							if (_user->getSocket() == vecUserInChannel[k].second)
								continue;
							std::string returnMessage = ":" + _user->getNickName();
							send(vecUserInChannel[k].second, messegeFromUser.c_str(), messegeFromUser.size(), IRC_NOSIGNAL);
						}
					}
				}
			}
		}
	}
}

void Command::joinToChannel_(const std::string & channelName, Channel * channel, std::vector<std::string> & passVec, size_t & iterPass)
{

	if (channelName[0] == '&')
	{
		channel->pushUserInChannel(_user->getNickName(), _user->getSocket());
	}
	else if (channelName[0] == '#')
	{

		if (passVec.size() == iterPass)
			throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
		if (passVec[iterPass] == channel->getPass())
			channel->pushUserInChannel(_user->getNickName(), _user->getSocket());
	}
}



void Command::cmdJoin()
{
	std::vector<std::string> param = _msg.getParams();
	if (param.size() < 1)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	std::vector<std::string> channelsJoin = split(param[0], ",");
	std::vector<std::string> channelPass;
	size_t iterPass = 0;
	if (param.size() == 2)
		channelPass = split(param[1], ",");
	for (size_t j = 0; j < channelsJoin.size(); ++j)
	{
		size_t i = 0;
		for (; i < _channels.size(); ++i)
		{
			if (_channels[i]->getChannelName() == channelsJoin[j].substr(1))
			{
				joinToChannel_(channelsJoin[j], _channels[i], channelPass, iterPass); // JOIN IN CHANNEL
				break;
			}
		}
		if (i == _channels.size() && channelsJoin[j][0] != '&' && channelsJoin[j][0] != '#') // PRINT ERROR MESSEGE
		{	

			errorRequest err(channelsJoin[j], ERR_NOSUCHCHANNEL);
			send(_user->getSocket(), err.what(), std::string(err.what()).size(), IRC_NOSIGNAL);
		}
		else if (i == _channels.size()) // CREATE CHANNEL 
		{
			std::string _pass = "";
			if (channelsJoin[j][i] == '#')
			{
				if (iterPass >= channelPass.size())
					 throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
				_pass = channelPass[iterPass];
				++iterPass;
			}
			Channel * A = new Channel(channelsJoin[j].substr(1), _pass, _user->getNickName());
			A->pushUserInChannel(_user->getNickName(), _user->getSocket());
			responseForCommand_(channelsJoin[j], RPL_NOTOPIC);
			responseForCommand_(channelsJoin[j], RPL_NAMREPLY);
			responseForCommand_(channelsJoin[j], RPL_ENDOFNAMES);
			_channels.push_back(A);
		}
	}
}

void Command::responseForCommand_(const std::string & msg, int numResponse) const
{
	std::string messege;
	switch (numResponse)
	{
		case RPL_NOTOPIC:
			messege = msg + " :No topic is set\n";
			break;
		case RPL_NAMREPLY:
			messege = msg + " :[[@|+]<nick> [[@|+]<nick> [...]]]\n"; // fix
			break;
		case RPL_ENDOFNAMES:
			messege = msg + " :End of /NAMES list\n"; // fix
			break;
		case RPL_NOWAWAY:
			messege = msg + " :You have been marked as being away";
			break;
		case RPL_UNAWAY:
			messege = msg + " :You are no longer marked as being away";
			break;
	}
	send(_user->getSocket(), messege.c_str(), messege.size(), IRC_NOSIGNAL);
}

void Command::cmdAway()
{
	if (_msg.getParams().size() > 0)
	{
		_user->setAwayFlag(1);
		_user->setAwayStatus(_msg.getParams()[0]);
		responseForCommand_("", RPL_NOWAWAY);
		return ;
	}
	_user->setAwayFlag(0);
	responseForCommand_("", RPL_UNAWAY);
	return;
}

void Command::cmdNotice()
{
	PrivMsg();
}