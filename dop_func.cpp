#include "Server.hpp"
#include "Message.hpp"
#include "User.hpp"
#include <cstring>

std::vector<std::string> split(const std::string str) {
	std::vector<std::string> result;
	std::vector<char> w(str.begin(), str.end());
	w.push_back('\0');
	char *pch = strtok(&w[0], " ");
	while (pch != NULL) {
		result.push_back(pch);
		pch = strtok(NULL, " ");
	}
	return result;
}