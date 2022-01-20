#include "Server.hpp"

int main(int ac, char **av) {
	if (ac == 3) {
		int port = atoi(av[1]);

		if (port < 1024 || port > 49151) {
			std::cout << "Wrong port!" << std::endl;
			return -1;
		}
		Server serv(atoi(av[1]), av[2]);
		serv.createSocket();
		serv.bindSocket();
		serv.listenSocket();
		while (1)
		{
			serv.acceptUsers();
			serv.receivingMessages();
		}
	}
}
