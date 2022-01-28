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
class Channel;

enum
{
    RPL_AWAY = 301,
    RPL_UNAWAY = 305,
    RPL_NOWAWAY = 306,
    RPL_NOTOPIC = 331, //       "<channel> :No topic is set"
    RPL_TOPIC = 332,

    RPL_INVITING = 341,
    RPL_NAMREPLY = 353, //      "<channel> :[[@|+]<nick> [[@|+]<nick> [...]]]" 
    RPL_ENDOFNAMES = 366, //    "<channel> :End of /NAMES list"
};

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
        std::string _servPass;
    public:
        Command(const Message & msg, User * user, std::vector<User *> & users, \
            std::vector<Channel *> & channels, std::string servPass);
        virtual ~Command();
        void checkConnection(void);
        void cmdPass(void);
	    void cmdUser(void);
	    void cmdNick(void);
        void PrivMsg(void);
        void cmdMode(void);
        void cmdNotice(void);
        void cmdAway(void);
        void cmdInvite(void);
        void cmdTopic(void);
        std::pair<std::vector<std::string>, std::string > getResponseForComand() const;
        void cmdJoin(void);
        void cmdKick();
        void cmdPart();
        void cmdNames();
        bool hasNickName(std::string param);
        bool onChannel(std::string channel);
        bool ClientOnChannel(std::string user, std::string channel);
        bool isOperator(std::string channel);
        std::string userAwayFlag(std::string user);
    private:
        Channel * findChannel_(const std::string & channel);
        User    * findUser_(const std::string & name);
        void responseForCommand_(const std::string & msg, int numResponse, const std::string &arg1) const;
        void createChannel_();
        void joinToChannel_(const std::string & channelName, Channel * channel, std::vector<std::string> & passVec, size_t & iterPass);
        void    addToChannel(std::string user, std::string channel);

};
