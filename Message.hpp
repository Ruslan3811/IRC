#pragma once

#include <iostream>
#include <vector>

class Message
{
private:
    std::string _cmd;
    std::vector<std::string> _parameters;
    std::string _trailing;
public:
    Message();
    ~Message();

    std::vector<std::string> getParams(void) const;
    void setParam(std::string param);
    
    std::string getCmd(void) const;
    void setCmd(std::string cmd);

    std::string getTrailing(void); 
};