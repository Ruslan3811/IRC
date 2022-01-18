#include "Server.hpp"
#include "Message.hpp"

#include <cstring>

Message::Message(const std::string str) : _prefix(""), _cmd("")
{
	std::vector<std::string> vec;
    
	vec = split(str);

    std::vector<std::string>::iterator i = vec.begin();

    if (vec.front()[0] == ':')
    {
        _prefix = vec.front();
        ++i;
    }
    
    for (; i != vec.end(); ++i)
    {
        if ((*i)[0] == ':')
            break;
        if ((*i)[0] != ':' && !_cmd.length())
            _cmd = *i;
        else if ((*i)[0] != ':')
            _parameters.push_back(*i);
    }

    std::cout << "PREFIX: " << _prefix << " CMD: " << _cmd << " " << " PARAMS: ";

    // for (i = params.begin(); i != params.end(); ++i)
    // {
    //     std::cout << *i;
    // }

    for (; i != vec.end(); ++i)
    {
        _trailing.push_back(*i);
    }

    for (i = _trailing.begin(); i != _trailing.end(); ++i)
    {
        std::cout << *i;
    }
    
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

std::vector<std::string> &Message::getTrailing()
{
    return _trailing;
}