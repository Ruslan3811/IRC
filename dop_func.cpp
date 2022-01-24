
#include <cstring>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string str, const char * ch)
{
	std::vector<std::string> result;
	std::vector<char> w(str.begin(), str.end());
	w.push_back('\0');
	char *pch = strtok(&w[0], ch);
	while (pch != NULL) {
		result.push_back(pch);
		pch = strtok(NULL, ch);
	}
	return result;
}