#include "Server.hpp"
#include "Cmd.hpp"
#include <string>

void printNum()
{
	static int i = 0;
	std::cout << ++i << std::endl;
}

void send_(const std::string & msg, int soket)
{
	send(soket, msg.c_str(), msg.size(), IRC_NOSIGNAL);
}

Channel * Command::findChannel_(const std::string & channel)
{
	for (size_t i = 0; i < _channels.size(); ++i)
	{
		if (channel == _channels[i]->getChannelName())
			return _channels[i];
	}
	return 0;

}
Command::Command(const Message & msg, User * user, std::vector<User *> & users, std::vector<Channel *> & channels, std::string servPass) 
: _msg(msg), _user(user), _users(users), _channels(channels), commandGiveResponse(false), _servPass(servPass)
{
	_command["PASS"] = &Command::cmdPass;
	_command["NICK"] = &Command::cmdNick;
	_command["USER"] = &Command::cmdUser;
	_command["PRIVMSG"] = &Command::PrivMsg;
	_command["JOIN"] = &Command::cmdJoin;
	_command["NOTICE"] = &Command::cmdNotice;
	_command["AWAY"] = &Command::cmdAway;
	_command["INVITE"] = &Command::cmdInvite;
	_command["MODE"] = &Command::cmdMode;
	_command["KICK"] = &Command::cmdKick;
	_command["PART"] = &Command::cmdPart;


	if (user->getRegistered() == false && msg.getCmd() != "PASS" && msg.getCmd() != "NICK" && msg.getCmd() != "USER")
		throw errorRequest(_msg.getCmd(), user->getNickName(), ERR_NOTREGISTERED);

	if (_command.find(msg.getCmd()) == _command.end())
		throw  errorRequest(_msg.getCmd(), _user->getNickName(), ERR_UNKNOWNCOMMAND);
	(this->*(_command.at(msg.getCmd())))();
}

Command::~Command() {}

void Command::checkConnection() {
	if (_user->getNickName().size() > 0 && _user->getUserName().size() > 0) {
		if (_servPass.size() == 0 || _user->getPassword() == _servPass) {
			if (_user->getRegistered() == false) {
				_user->setRegistered(true);
				send_("Registration complete!\n", _user->getSocket());
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
					std::string returnMessage = "From: " + _user->getNickName() + " To: " + _users[j]->getNickName() + " PRIVMSG: " + messegeFromUser;
					send(_users[j]->getSocket(), returnMessage.c_str(), returnMessage.size(), IRC_NOSIGNAL);
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
							std::string returnMessage = "From: " + _channels[j]->getChannelName() + ", " + _user->getNickName() + " To: " + vecUserInChannel[k].first + " PRIVMSG: " + messegeFromUser;
							send(vecUserInChannel[k].second, returnMessage.c_str(), returnMessage.size(), IRC_NOSIGNAL);
						}
					}
				}
			}
		}
	}
}

void Command::joinToChannel_(const std::string & channelName, Channel * channel, std::vector<std::string> & passVec, size_t & iterPass)
{
	if (channel->getOnlyInvaite())
		{
			bool userInvate = false;
			std::vector<std::string> invaiteList = channel->getInviteListVec();
			for (size_t i = 0; i < invaiteList.size(); ++i)
			{
				if (_user->getNickName() == invaiteList[i])
				{
					userInvate = true;
					break;
				}
			}
			if (userInvate == false)
				throw errorRequest(channel->getChannelName(), ERR_INVITEONLYCHAN);
		}
	if (channel->getCountUser() >= channel->getUserInChannel().size())
		throw errorRequest(channel->getChannelName(), ERR_CHANNELISFULL);
	if (channel->getBanMask() != "" && _user->getNickName().find(channel->getBanMask()) != std::string::npos)
		throw errorRequest(channel->getChannelName(), ERR_BADCHANMASK);
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
	_user->pushChannelName(channelName);
	std::string returnMessage = ":" + _user->getNickName() + "!" + _user->getUserName() + "@" + _user->getHostName() + " JOIN: " + channelName + "\n";
	send(_user->getSocket(), returnMessage.c_str(), returnMessage.size(), IRC_NOSIGNAL);
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
			if (_channels[i]->getChannelName() == channelsJoin[j])
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
			Channel * A = new Channel(channelsJoin[j], _pass, _user->getNickName());
			A->pushUserInChannel(_user->getNickName(), _user->getSocket());
			std::string returnMessage = ":" + _user->getNickName() + "!" + _user->getUserName() + "@" + _user->getHostName() + " JOIN: " + channelsJoin[j] + "\n";
			send(_user->getSocket(), returnMessage.c_str(), returnMessage.size(), IRC_NOSIGNAL);
			responseForCommand_(channelsJoin[j], RPL_NOTOPIC);
			responseForCommand_(channelsJoin[j], RPL_NAMREPLY);
			responseForCommand_(channelsJoin[j], RPL_ENDOFNAMES);
			_channels.push_back(A);
			_user->pushChannelName(A->getChannelName());
		}
	}
}

void Command::responseForCommand_(const std::string & msg, int numResponse) const
{
	std::string messege;
	switch (numResponse)
	{
		case RPL_NOTOPIC:
			messege = ":" + _user->getServerName() + " 331 " + _user->getNickName() + " " + msg + " :No topic is set\n";
			break;
		case RPL_NAMREPLY:
			messege = ":" + _user->getServerName() + " 353 " + _user->getNickName() + " = " + msg + " :@" + _user->getNickName() + "\n";
			break;
		case RPL_ENDOFNAMES:
			messege = ":" + _user->getServerName() + " 366 " + _user->getNickName() + " " + msg + " :End of /NAMES list\n";
			break;
		case RPL_NOWAWAY:
			messege = msg + " :You have been marked as being away\n";
			break;
		case RPL_UNAWAY:
			messege = msg + " :You are no longer marked as being away\n";
			break;
		case RPL_AWAY:
			messege = msg + "\n";
			break;
		case RPL_INVITING:
			messege = msg + "\n";
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

bool Command::hasNickName(std::string param)
{
	std::vector<User *>::iterator begin = _users.begin();
	std::vector<User *>::iterator end = _users.end();
	for (;begin != end; ++begin)
	{
		if (param == (*begin)->getNickName())
			return (true);
	}
	return (false);
}

User    * Command::findUser_(const std::string & name)
{
	for (size_t i = 0; i < _users.size(); ++i)
	{
		if (_users[i]->getNickName() == name)
			return _users[i];
	}
	return (0);
}

bool Command::onChannel(std::string channel)
{
	std::vector<std::string>::iterator begin = _user->getAllChannel().begin();
	std::vector<std::string>::iterator end = _user->getAllChannel().end();
	for (;begin != end; ++begin)
	{
		if ((*begin) == channel)
			return true;
	}
	return (false);
}

bool Command::ClientOnChannel(std::string user, std::string channel)
{
	std::vector<User *>::iterator begin = _users.begin();
	std::vector<User *>::iterator end = _users.end();
	std::vector<std::string> channels;
	for (; begin!= end; ++begin)
	{
		if ((*begin)->getNickName() == user)
			channels = (*begin)->getAllChannel();
	}
	std::vector<std::string>::iterator begin_ch = channels.begin();
	std::vector<std::string>::iterator end_ch = channels.end();
	for (; begin_ch!= end_ch; ++begin_ch)
	{
		if ((*begin_ch) == channel)
			return true;
	}
	return false;
}

bool Command::isOperator(std::string channel)
{
	std::vector<Channel *>::iterator begin = _channels.begin();
	std::vector<Channel *>::iterator end = _channels.end();

	for (;begin != end; ++begin)
	{
		if ((*begin)->getChannelName() == channel && (*begin)->getHostName() != _user->getNickName() && (*begin)->isPrivateChannel())
			return false;
	}
	return true;
}

std::string Command::userAwayFlag(std::string user)
{
	std::vector<User *>::iterator begin = _users.begin();
	std::vector<User *>::iterator end = _users.end();

	for (;begin != end; ++begin)
	{
		if ((*begin)->getNickName() == user)
			return (*begin)->getAwayStatus();
	}
	return ("");
}

void Command::cmdInvite()
{
	if (_msg.getParams().size() < 2)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	else if (!hasNickName(_msg.getParams()[0]))
		throw errorRequest(_msg.getParams()[0], _user->getNickName(), ERR_NOSUCHNICK);
	else if (!onChannel(_msg.getParams()[1]))
		throw errorRequest(_msg.getParams()[1], _user->getNickName(), ERR_NOTONCHANNEL);
	else if (ClientOnChannel(_msg.getParams()[0], _msg.getParams()[1]))
		throw errorRequest(_msg.getParams()[0], ERR_USERONCHANNEL);
	else if (!isOperator(_msg.getParams()[1]))
		throw errorRequest(_msg.getParams()[1], _user->getNickName(), ERR_CHANOPRIVSNEEDED);
	if (userAwayFlag(_msg.getParams()[0]).length() > 0)
		responseForCommand_(_msg.getParams()[0] + " " + userAwayFlag(_msg.getParams()[0]), RPL_AWAY);
	responseForCommand_(_msg.getParams()[1] + " " + _msg.getParams()[0], RPL_INVITING);
	Channel *ch = findChannel_(_msg.getParams()[1]);
	ch->pushInviteListVec(_msg.getParams()[0]);
}

//NICKNAME
//Active

void Command::cmdMode()
{
	std::vector<std::string> param = _msg.getParams();
	size_t countParam = 2;

	bool	operation = true;
	if (param.size() < countParam)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	Channel * channel = findChannel_(param[0]);
	if (channel == 0)
		throw errorRequest(param[0], ERR_NOTONCHANNEL);
	if (_user->getNickName() != channel->getHostName())
		throw errorRequest(_user->getNickName(), ERR_USERSDONTMATCH);
	User * user;
	for (size_t i = 0; i < param[1].size(); ++i)
	{
		if (param[1][i] == 'l' || param[1][i] == 'b' || param[1][i] == 'o' || param[1][i] == 'o')
		{
			++countParam;
			if (param.size() < countParam)
				throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
		}
		switch (param[1][i])
		{
		case '+':
			operation = true;
			break;
		case '-':
			operation = false;
			break;
		case 'o':
			user = findUser_(param[countParam - 1]);
			if (user == 0)
				throw errorRequest(param[countParam - 1], ERR_NOSUCHNICK);
			channel->setHostName(param[countParam - 1]);
			send_("Set host name!\n", _user->getSocket());
			break;
		case 'p':
			channel->setPrivateChannel(operation);
			send_("Set private channel!\n", _user->getSocket());
			break;
		case 's':
			channel->setSecretChannel(operation);
			send_("Set secret channel!\n", _user->getSocket());
			break;
		case 'i':
			channel->setOnlyInvaite(operation);
			send_("Set only invaite!\n", _user->getSocket());

			break;
		case 't':
			if (channel->getOnlyInvaite() == true && _user->getNickName() != channel->getHostName())
				throw errorRequest(_user->getNickName(), ERR_CHANOPRIVSNEEDED);
			break;
		case 'm':
			channel->setModerChannel(operation);
			send_("Set moder channel!\n", _user->getSocket());
			break;
		case 'l':
			channel->setCountUser(atoi(param[countParam - 1].c_str()));
			send_("Set Count User!", _user->getSocket());
			break;
		case 'b':
			channel->setBanMask(param[countParam - 1]);
			send_("Set Ban Mask!\n", _user->getSocket());

			break;
		case 'k':
			channel->setPass(param[countParam - 1]);
			send_("Set pass!\n", _user->getSocket());
			break;
		default:
			throw errorRequest("" + param[1][i], ERR_UMODEUNKNOWNFLAG);
		}
	}
	
}

void Command::cmdKick()
{
	Channel *channel = findChannel_(_msg.getParams()[0]);
	if (_msg.getParams().size() < 2)
		throw errorRequest(_msg.getCmd(), _user->getNickName(), ERR_NEEDMOREPARAMS);
	std::string chan = _msg.getParams()[0];
	std::string user = _msg.getParams()[1];
	if (!isOperator(user) && !_msg.getPrefix().length())
		throw errorRequest(user, _user->getNickName(), ERR_CHANOPRIVSNEEDED);
	if (!onChannel(chan))
		throw errorRequest(user, _user->getNickName(), ERR_NOTONCHANNEL);
	if (!channel)
		throw errorRequest(chan, _user->getNickName(), ERR_NOSUCHCHANNEL);
	if (channel->getBanMask() != "" && _user->getNickName().find(channel->getBanMask()) != std::string::npos)
		throw errorRequest(channel->getChannelName(), ERR_BADCHANMASK);
	if (_msg.getTrailing().length() > 0)
	{
		send_("Kick " + user + " from " +chan + "\n", findUser_(channel->getHostName())->getSocket());
		send_("You are kicked from " + chan + "\n", findUser_(chan)->getSocket());
	}
	else
	{
		User *kicked_user = findUser_(user);
		if (kicked_user == 0)
			throw errorRequest(user, _user->getNickName(), ERR_CHANOPRIVSNEEDED);
		kicked_user->eraseOneChannel(chan);
		channel->eraseUserForChannel(user, findUser_(user)->getSocket());
		channel->eraseUserForInvaiteList(user);

		if (_msg.getTrailing().length() > 0)
			send_(":" + _msg.getTrailing(), _user->getSocket());
	}
		
}

void Command::cmdPart() {
	std::vector<std::string> param = _msg.getParams();
	std::vector<std::string> channels = split(param[0], ",");
	if (channels.size() < 1)
		throw errorRequest(_msg.getCmd(), ERR_NEEDMOREPARAMS);
	std::vector<std::string>::iterator it = channels.begin();
	std::vector<std::string>::iterator it2 = channels.end();
	std::vector<std::string> vec_ch;
	// for (size_t i; i < _user->getAllChannel().size(); ++i) {
	// 	std::cout << _user->getAllChannel()[i] << " ";
	// }
	// std::cout << std::endl;
	for (; it != it2; ++it) {
		if (!onChannel(*it))
			throw errorRequest(*it, ERR_NOTONCHANNEL);
		else if (!findChannel_(*it))
			throw errorRequest(*it, ERR_NOSUCHCHANNEL);
		else {
			for (size_t i = 0; i < _user->getAllChannel().size(); ++i) {
				if (*it == _user->getAllChannel()[i]) {
					_user->eraseOneChannel(*it);
					vec_ch.push_back(*it);
				}
			}
		}
	}
	std::string deleteChannels;
	for (size_t i = 0; i < vec_ch.size(); ++i)
		deleteChannels += vec_ch[i] + " ";
	std::string returnMessage = ":" + _user->getNickName() + "!" + _user->getUserName() + "@" + _user->getHostName() + " PART:" + deleteChannels + "\n";
	send_(returnMessage, _user->getSocket());
}
