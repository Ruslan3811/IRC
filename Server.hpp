#pragma once

#include <iostream>
#include "Message.hpp"
#include "User.hpp"
#include "Errors.hpp"
#include <sys/socket.h>
#include <string>

class Server
{
public:
    Server();
    ~Server();
    int passCmd(Message &msg, User &user);
};