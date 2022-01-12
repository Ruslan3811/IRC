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

class Server {
private:
	int					_port;
	std::string			_password;
	int					_listening;
	sockaddr_in			_sockaddr;
	std::vector<pollfd>	_fdUsers;

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
};

void exita(std::string msg);