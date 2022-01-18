#include "Server.hpp"
#include "Message.hpp"

Message::Message(const std::string str){
	std::vector<std::string> vec;
	vec = split(str);
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