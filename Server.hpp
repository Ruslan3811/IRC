#pragma once

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <poll.h>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>

#include <cstdlib>
#include <errno.h>
#include <fstream>
#include <map>
#include "Cmd.hpp"

class User;
class Server;

// typedef int (Server::*Cmd) (Message &, User &);

class Server {
private:
	int					_port;
	std::string			_password;
	int					_listening;
	sockaddr_in			_sockaddr;
	std::vector<pollfd>	_fdUsers;
	std::vector<User *>	_UsersAccept;
	std::string			_serverName;
	std::string 		_hostname;
	int					_clientSocket;
	// std::map<std::string, Cmd> _command;

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
	void receivingMessages();
	Message parseMsg(const int idx);

	int getPort() const { return _port; }
	const std::string& getPassword() const { return _password; }
	int getClientSocket() const { return _clientSocket; }

	void setServerName(std::string servername);
	std::string getServerName(void) const;

	void setHostName(std::string hostname);
	std::string getHostName(void) const;

	std::vector<User *> getUsers() const;
};

void exita(std::string msg);