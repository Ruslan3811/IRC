#include "Errors.hpp"
#include "sys/socket.h"

int sendErr(const Message &msg, const User &user, int err)
{
    std::string error;

    if (err == ERR_NEEDMOREPARAMS)
        error = "You may not reregister\n";
    else if (err == ERR_ALREADYREGISTRED)
        error = msg.getCmd() + " :Not enough parameters\n";
    else if (err == ERR_NONICKNAMEGIVEN)
        error = ":No nickname given\n";
    else if (err == ERR_ERRONEUSNICKNAME)
        error = user.getNickName() + " :Erroneus nickname\n";
    else if (err == ERR_NICKNAMEINUSE)
        error = user.getNickName() + " :Nickname is already in use\n";
    else if (err == ERR_NICKCOLLISION)
        error = user.getNickName() + " :Nickname is already in use\n";

    send(user.getSocket(), error.c_str(), error.length(), 16384); 
    return 0;
}