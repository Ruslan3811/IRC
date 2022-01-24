#include "Server.hpp"

User::User(int socket, std::string host) 
: _socket(socket), _host(host), _password(""), _nickname(""), _username(""),_hostname(""), _servername(""), _realname("")
{
	_flag = 0;
	_registered = false;
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

void User::setNickName(std::string nickname) { _nickname = nickname; }

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

std::string User::getRealName()const
{
	return _realname;
}

std::string User::getNickName()const
{
	return _nickname;
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
		if (bytesRecv >= 0) {
			buf[bytesRecv] = 0;
			msg += buf;
			std::cout  << msg;
			if (msg.find('\n') != std::string::npos) {
				if (msg[0] != '\n')
					msg.erase(msg.find('\n'), 1);
				break;
			}
		}
		if (bytesRecv < 0) {
			return (-1);
		}
	}
	_message.push_back(msg);
	return (0);
}

std::vector<std::string> User::getMessage() const { return _message; }

bool User::getRegistered() const { return _registered; }
void User::setRegistered(bool registered) { _registered = registered; }


int User::getfPass() const { return _fPass; }


void User::nullify_flag()
{

}

 void User::setAwayMsg(std::string msg)
 {
	_away_msg = msg;
 }
std::string User::getPassword()const { return _password; }
