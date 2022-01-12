#include "Server.hpp"

Message::Message(){}

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