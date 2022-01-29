#include "Server.hpp"

User::User(int socket, std::string host, std::string servername) 
: _socket(socket), _host(host), _password(""), _nickname(""), _username(""), _servername(servername), _realname("")
{
	_active = true;
	_registered = false;
	_secretUser = false;
}

User::User(void) {}

User::~User(void){}

void User::setUserRealName(std::string realname)
{
    _realname = realname;
}

void User::setUserName(std::string username)
{
    _username = username;
}

void User::setNickName(std::string nickname) { _nickname = nickname; }



bool User::getActive() const { return _active; }

std::vector<std::string> & User::getAllChannel()
{
	return _channels;
}

void User::eraseOneChannel(const std::string & name)
{
	std::vector<std::string>::iterator it = std::find(_channels.begin(), _channels.end(), name);
    if (it != _channels.end())
        _channels.erase(it);
}

void User::pushChannelName(const std::string & channel)
{
	_channels.push_back(channel);
}

void User::eraseAllChannel()
{
	_channels.erase(_channels.begin(), _channels.end());
}

int User::IsTrueLength(std::string str)
{
    return str.length();
}

bool User::isAlreadyRegistered(void) const
{
    return _registered;
}


void User::setPassword(std::string password)
{
    _password = password;
}

int User::getSocket()const
{
    return _socket;
}

std::string User::getRealName()const
{
	return _realname;
}

std::string User::getNickName()const
{
	return _nickname;
}

bool User::getAwayMassageStatus() const
{
	return _noAwayMassage;
}

void User::setAwayMassageStatus(bool b)
{
	_noAwayMassage = b;
}

std::string User::getUserName()const { return _username; }

bool User::isActiveUser()const
{
	return _active;
}

void User::setActiveUser(bool active)
{
	_active = active;
}

// Alena
int User::readMsg() {
	char buf[4096];
	std::string msg;

	for(;;) {
		// Clear the buffer
		memset(buf, 0, 4096);

		// Wait for a message
		int bytesRecv = recv(_socket, buf, 4096, 0);
		if (bytesRecv > 0) {
			buf[bytesRecv] = 0;
			msg += buf;
			if (msg == "\n" || msg == "")
			{
				msg = "";
				continue;
			}
			std::cout  << msg;
			if (msg.find('\n') != std::string::npos) {
				if (msg[0] != '\n')
					msg.erase(msg.find('\n'), 1);
				break;
			}
		}
		if (bytesRecv <= 0)
			return (-1);
	}
	_message.push_back(msg);
	return (0);
}

std::vector<std::string> User::getMessage() const { return _message; }

bool User::getRegistered() const { return _registered; }
void User::setRegistered(bool registered) { _registered = registered; }

std::string User::getAwayStatus()const
{
	return _away_status;
}


 void User::setAwayStatus(std::string msg)
 {
	_away_status = msg;
 }

std::string User::getHostName() const { return _host; }
std::string User::getPassword()const { return _password; }
std::string User::getServerName()const { return _servername; }