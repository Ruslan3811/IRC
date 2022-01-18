#include "Server.hpp"
#include <cstring>

Message::Message(const std::string str)
{
    std::string tmp_str = str;
    std::string cmd = "";
    std::vector<std::string> params;
    std::vector<std::string> trailing;
    
    std::size_t found = str.find(' ');
    if (str[0] != ' ' && found == std::string::npos)
    {
        cmd = str;
        std::cout << "First condition\n" << found;
    }
    else if (str[0] != ':')
    {
        cmd = tmp_str.substr(0, found);
        tmp_str.erase(0, found + 1);
    }
    std::cout << tmp_str;
    
    
}

Message::~Message(){}

std::vector<std::string> Message::getParams(void)const
{
    return _parameters;
}

void Message::setParam(std::string param)
{
    _parameters.push_back(param);
}
    
std::string Message::getCmd(void) const
{
    return _cmd;
}

void Message::setCmd(std::string cmd)
{
    _cmd = cmd;
}

std::string Message::getTrailing()
{
    return _trailing;
}