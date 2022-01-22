#pragma once
#include "Message.hpp"
#include "Exception.hpp"
#include "User.hpp"
#include <map>

class Message;
class User;
class Command;

typedef void (Command::*Cmd) (void);

class  Command
{
    private:
        Message _msg;
        User    *_user;
        std::vector<User *> & _users;
		std::map<std::string, Cmd> _command;

    public:
        Command(const Message & msg, User * user, std::vector<User *> & users);
        void cmdPass(void);
	    void cmdUser(void);
	    void cmdNick(void);

        void cmdMode(void);
};
