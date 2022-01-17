#pragma once

#include <iostream>
#include "User.hpp"
#include "Message.hpp"
#include <sys/socket.h>

class User;
class Message;

enum ERRORS
{
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    
    ERR_NICKCOLLISION = 436,

    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
};

int sendErr(const Message &msg, const User &user, int err);
