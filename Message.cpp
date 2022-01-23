#include "Server.hpp"
#include "Message.hpp"

#include <cstring>

Message::Message(const std::string str) : _prefix(""), _cmd("")
{
    std::cout << "START" << std::endl;


	std::vector<std::string> vec;
    
	vec = split(str);

    std::vector<std::string>::iterator i = vec.begin();

    if (vec.front()[0] == ':')
    {
        _prefix = vec.front();
        ++i;
    }
    _prefix.erase(0, 1);

    for (; i != vec.end(); ++i)
    {
        if ((*i)[0] == ':')
            break;
        if ((*i)[0] != ':' && !_cmd.length())
            _cmd = *i;
        else if ((*i)[0] != ':')
            _parameters.push_back(*i);
    }

    for (; i != vec.end(); ++i)
    {
        _trailing += (*i) + " ";
    }
    if (_trailing.length() > 0)
    {
        _trailing.erase(0, 1);
        _trailing.erase(_trailing.length() - 1, 1);
    }

    //TEST
    std::cout << "PREFIX: |" << _prefix << "|" << std::endl;
    std::cout << "CMD: |" << _cmd << "|" << std::endl;
    std::vector<std::string>::iterator ind = _parameters.begin();
    std::cout << "PARAMS: |";
    for(; ind != _parameters.end(); ++ind)
        std::cout << *ind << "|";
    std::cout << "\nTRAILING: |" << _trailing << "|" << std::endl;
    std::cout << "END" << std::endl;
    // std::cout << getCmd() << "\n" ;
    //Если понадобится вектор
    // for (; i != vec.end(); ++i)
    // {
    //     _trailing.push_back(*i);
    // }

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

//Если пондобится вектор
// std::vector<std::string> &Message::getTrailing()
// {
//     return _trailing;
// }

std::string &Message::getTrailing()
{
    return _trailing;
}

std::string &Message::getPrefix()
{
    return _prefix;
}