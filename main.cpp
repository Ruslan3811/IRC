#include "Server.hpp"

int main(int ac, char **av) {
	if (ac == 3) {
		int port = atoi(av[1]);

		if (port < 1024 || port > 49151) {
			std::cout << "Wrong port!" << std::endl;
			return -1;
		}
		Server serv(atoi(av[1]), av[2]);

		// Create a socket
		serv.createSocket();

		// Bind the socket to a IP / port
		serv.bindSocket();

		// Mark the socket for listening in
		serv.listenSocket();

		for(;;) {
			// Accept a call
			serv.acceptUsers();
			// While receiving - display message, echo message
			// Close socket

		}
	}
}
