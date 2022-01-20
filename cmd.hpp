#pragma once
#include "Message.hpp"
#include "User.hpp"


class  Command
{
    private:
        Message _msg;
        User    _user;

    public:
        Command(const Message & msg,const User & user);
        void cmdPass(void);
	    void cmdUser(void);
	    void cmdNick(void);
};
