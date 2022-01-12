#include "Errors.hpp"
#include "sys/socket.h"

int sendErr(const Message &msg, const User &user, int err)
{
    std::string error;

    if (err == ERR_NEEDMOREPARAMS)
        error = "You may not reregister\n";
    else if (err == ERR_ALREADYREGISTRED)
        error = msg.getCmd() + " Not enough parameters\n";
    // std::cout << error;
    send(user.getSocket(), error.c_str(), error.length(), 16384); 
    return 0;
}