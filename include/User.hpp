#pragma once

#include <iostream>
#include "Message.hpp"
#include "CodeError.hpp"
class User
{
private:
    int                         _socket;
    std::string                 _host;
    std::string                 _password;
    std::string                 _nickname;
    std::string                 _username;
    std::string                 _servername;
    std::string                 _realname;
    std::string                 _away_status;

	std::vector<std::string>    _message;
    std::vector<std::string>    _channels;

    bool                        _active;
	bool		                _registered;
    bool                        _secretUser;
    bool                        _noAwayMassage;


    User();
public:
    ~User();

    User(int socket, std::string host, std::string servername);

    void eraseOneChannel(const std::string & name);
    void eraseAllChannel();

    int IsTrueLength(std::string str);

    // Alena
    int readMsg();

    int                         getfPass() const;
    int                         getSocket()const;
    bool                        getActive() const;
    bool                        isActiveUser() const;
	bool                        getRegistered() const;
    bool                        isAlreadyRegistered(void) const;
    bool                        getAwayMassageStatus() const;
    std::string                 getHostName()const;
    std::string                 getPassword()const;
    std::string                 getNickName()const;
    std::string                 getUserName()const;
    std::string                 getRealName()const;
    std::string                 getAwayStatus()const;
    std::string                 getServerName()const;
	std::vector<std::string>    getMessage() const;
    std::vector<std::string> &  getAllChannel();

    void                        setPassword(std::string password);
    void                        setUserName(std::string username);
    void                        setNickName(std::string nickname);
	void                        setRegistered(bool registered);
    void                        setActiveUser(bool active);
    void                        setAwayStatus(std::string msg);
    void                        pushChannelName(const std::string &);
    void                        setUserRealName(std::string realname);
    void                        setAwayMassageStatus(bool);



};