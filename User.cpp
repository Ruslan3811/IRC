#include "Server.hpp"

User::User(int socket, std::string host) 
: _socket(socket), _host(host), _username(""), _password(""), _realname("")
{
	_flag = 0;
	_registered = 0;
}

User::User(void): _flag(0){}

User::~User(void){}

void User::setUserRealName(std::string realname)
{
    _realname = realname;
}

void User::setUserName(std::string username)
{
    _username = username;
}

void User::setSocket(int sock)
{
    _socket = sock;
}

int User::getFlag()const
{
    return _flag;
}

int User::IsTrueLength(std::string str)
{
    return str.length();
}

bool User::isAlreadyRegistered(void)const
{
    if (getFlag() == ERR_ALREADYREGISTRED)
        return true;
    return false;
}

void User::setFlag(int flag)
{
    _flag = flag;
}

void User::setPassword(std::string password)
{
    _password = password;
}

int User::getSocket()const
{
    return _socket;
}

std::string User::getNickName()const
{
	return _username;
}

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
			std::cout  << msg;
			if (msg.find('\n') != std::string::npos) {
				if (msg[0] != '\n')
					msg.erase(msg.find('\n'), 1);
				break;
			}
		}
		if (bytesRecv <= 0) {
			return (-1);
		}
	}
	_message.push_back(msg);
	return (0);
}

std::vector<std::string> User::getMessage() const { return _message; }

int User::getRegistered() const { return _registered; }

void User::setRegistered(int registered) { _registered += registered; }
