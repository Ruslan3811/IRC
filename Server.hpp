#pragma once

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <poll.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstdlib>
#include <errno.h>
#include <fstream>
#include <map>

#include "User.hpp"

class Server {
private:
	int					_port;
	std::string			_password;
	int					_listening;
	sockaddr_in			_sockaddr;
	std::vector<pollfd>	_fdUsers;
	std::vector<User *>	_UsersAccept;
	std::string			_servername;
	std::string 		_hostname;

	Server();
	Server(const Server& copy);
	Server	&operator=(const Server& other);
public:
	Server(int port, const std::string &password);
	virtual ~Server();

	void createSocket();
	void bindSocket();
	void listenSocket();
	void acceptUsers();

	int getPort() const { return _port; }
	const std::string& getPassword() const { return _password; }

	int cmdPass(Message &msg, User &user);
	int cmdUser(Message &msg, User &user);

	void setServerName(std::string servername);
	std::string getServerName(void) const;

	void setHostName(std::string hostname);
	std::string getHostName(void) const;
};

void exita(std::string msg);