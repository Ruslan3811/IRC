

#include "dop_function.hpp"
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

void printVectorPair(const std::vector<std::pair<std::string, int> > & vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << "nick: " << vec[i].first << " id " << vec[i].second << std::endl;
	}
}

void printVectorString(const std::vector<std::string> & vec)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << "nick invite: " << vec[i]  << " ";
	}
	std::cout << std::endl;
}