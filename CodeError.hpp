#pragma once

enum ERRORS
{
    ERR_NOSUCHNICK =        401,
    ERR_NOSUCHCHANNEL =     403,
    ERR_UNKNOWNCOMMAND =    421,
    ERR_NONICKNAMEGIVEN =   431,
    ERR_ERRONEUSNICKNAME =  432,
    ERR_NICKNAMEINUSE =     433,
    ERR_NICKCOLLISION =     436,
    ERR_NOTREGISTERED =     451,
    ERR_NEEDMOREPARAMS =    461,
    ERR_ALREADYREGISTRED =  462,
};
