#include "Server.hpp"



void Server::setServerName(std::string servername)
{
	_serverName = servername;
}

std::string Server::getServerName(void) const
{
	return _serverName;
}

void Server::setHostName(std::string hostname)
{
	_hostname = hostname;
}

std::string Server::getHostName(void) const
{
	return _hostname;
}

void exita(std::string msg) {
	std::cerr << msg << std::endl;
	exit(1);
}

Server::Server() {
	_serverName = "IRC";
}

Server::Server(int port, const std::string &password) : _port(port), _password(password) {
	_serverName = "IRC";
}

Server::~Server() {
	std::vector<User *>::iterator it = _UsersAccept.begin();
	std::vector<User *>::iterator it2 = _UsersAccept.end();
	for (; it != it2; ++it) {
		close((*it)->getSocket());
		delete *it;
	}
}

void Server::createSocket() {
	_listening = socket(AF_INET, SOCK_STREAM, 0);
	if (_listening == -1)
		exita("Can`t create a socket!");
}

void Server::bindSocket() {
	int optval = 1;
	_sockaddr.sin_family = AF_INET;
	_sockaddr.sin_port = htons(_port);
	_sockaddr.sin_addr.s_addr = 0UL;//inet_addr("127.0.0.1");//0UL; // здесь должен быть IP из конфига
	if ((setsockopt(_listening, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1) {
		close(_listening);
		exita("ERROR Set Socket!");
	}
	if (bind(_listening, (struct sockaddr *)&_sockaddr, sizeof(_sockaddr)) < 0) {
		close(_listening);
		exita("Can`t bind to IP/port");
	}
}

void Server::listenSocket() {
	if (listen(_listening, SOMAXCONN) == -1) {
		close(_listening);
		exita("Can`t listen!");
	}
	fcntl(_listening, F_SETFL, O_NONBLOCK);
}

void Server::acceptUsers() {
	sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	_clientSocket = accept(_listening, (sockaddr *)&client, &clientSize);
	if (_clientSocket >= 0) {
		char host[INET_ADDRSTRLEN];
		memset(host, 0, INET_ADDRSTRLEN);
		inet_ntop(AF_INET, &(client.sin_addr), host, INET_ADDRSTRLEN);
		std::cout << host << " connect on " << ntohs(client.sin_port) << std::endl;
		pollfd pfd;
		pfd.fd = _clientSocket;
		pfd.events = POLLIN;
		pfd.revents = POLLERR;
		_fdUsers.push_back(pfd);
		User *a = new User(_clientSocket, host, _serverName);
		_UsersAccept.push_back(a);
	} 
}

void Server::receivingMessages() {
	int ret = poll(_fdUsers.data(), _fdUsers.size(), 1000);
	if (ret > 0) {
		std::vector<pollfd>::iterator it = _fdUsers.begin();
		std::vector<pollfd>::iterator it2 = _fdUsers.end();
		for (; it != it2; ++it) {
			if (it->revents == POLLIN) { // если произошло событие
				int idx = it - _fdUsers.begin();
				// читаем сообщение
				if (_UsersAccept[idx]->readMsg() == -1)
				{
					_UsersAccept[idx]->setFlag(-1);
				}

				try
				{
					std::vector<std::string> msg = _UsersAccept[idx]->getMessage();
					if (msg.size() != 0)
					{
						Message message(*(--msg.end()));
						Command A(message, _UsersAccept[idx], _UsersAccept, _channels, _password);
					}

				}
				catch (const std::exception & ex)
				{
					send(_UsersAccept[idx]->getSocket(), ex.what(), std::string(ex.what()).size(), IRC_NOSIGNAL);
				}
			

			}
			it->revents = 0; // обнуляем revents, чтобы можно было пeреиспользовать структуру
		}
	}
}

std::vector<User *> Server::getUsers()const
{
	return _UsersAccept;
}
