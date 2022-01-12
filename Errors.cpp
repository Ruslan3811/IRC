#include "Errors.hpp"
#include "sys/socket.h"

int sendErr(const Message &msg, const User &user)
{
    std::string error;

    if (user.getFlag() == ERR_NEEDMOREPARAMS)
        error = "You may not reregister\n";
    else if (user.getFlag() == ERR_ALREADYREGISTRED)
        error = msg.getCmd() + " Not enough parameters\n";
    // std::cout << error;
    send(user.getSocket(), error.c_str(), error.length(), 16384); 
    return 0;
}