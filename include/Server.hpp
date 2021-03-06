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
#include "User.hpp"
#include "Message.hpp"
#include "Exception.hpp"
#include "dop_function.hpp"
#include "Channel.hpp"
#ifdef __APPLE__
#define IRC_NOSIGNAL SO_NOSIGPIPE
#else
#define IRC_NOSIGNAL MSG_NOSIGNAL
#endif

class User;
class Server;

// typedef int (Server::*Cmd) (Message &, User &);

class Server {
private:
	int						_port;
	std::string				_password;
	int						_listening;
	sockaddr_in				_sockaddr;
	std::vector<pollfd>		_fdUsers;
	std::vector<User *>		_UsersAccept;
	std::vector<Channel *> 	_channels;
	std::string				_serverName;
	std::string 			_hostname;
	int						_clientSocket;
	// std::map<std::string, Cmd> _command;

	Server(const Server& copy);
	Server	&operator=(const Server& other);
	Server();
public:
	Server(int port, const std::string &password);
	virtual ~Server();

	void createSocket();
	void bindSocket();
	void listenSocket();
	void acceptUsers();
	void receivingMessages();
	void deleteNotActiveUsers();
	Message parseMsg(const int idx);


	int 				getPort() const { return _port; }
	const std::string& 	getPassword() const { return _password; }
	int 				getClientSocket() const { return _clientSocket; }
	std::string 		getServerName(void) const;
	std::string 		getHostName(void) const;
	std::vector<User *> getUsers() const;


	void 				setServerName(std::string servername);
	void 				setHostName(std::string hostname);

};

void exita(std::string msg);