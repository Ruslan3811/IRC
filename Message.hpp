#pragma once

#include "dop_function.hpp"

class Message
{
private:
    std::string _prefix;
    std::string _cmd;
    std::vector<std::string> _parameters;
    std::string _trailing;
public:
    Message(const std::string str);
    ~Message();

    std::vector<std::string> getParams(void) const;
    void setParam(std::string param);
    
    std::string getCmd(void) const;
    void setCmd(std::string cmd);

    std::string &getTrailing();
    std::string &getPrefix();
};

// Alena