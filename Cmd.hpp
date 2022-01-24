#pragma once
#include "Message.hpp"
#include "Exception.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include <map>
#include <vector>

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
        std::vector<Channel *> & _channels;
        std::pair<std::vector<std::string>, std::string> _response;
        bool    commandGiveResponse;
    public:
        Command(const Message & msg, User * user, std::vector<User *> & users, std::vector<Channel *> & channels);
        void cmdPass(void);
	    void cmdUser(void);
	    void cmdNick(void);
        void PrivMsg(void);
        void cmdMode(void);
        void cmdNotice(void);
        void cmdAway(void);
        std::pair<std::vector<std::string>, std::string > getResponseForComand() const;
};
