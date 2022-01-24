#include "Exception.hpp"
#include "CodeError.hpp"

std::string errorRequest::_getErrorMessage(int codeError)
{
	switch (codeError)
	{
		case ERR_NOSUCHNICK:
			return _msg + " :No such nick/channel\n";
		case ERR_NOSUCHSERVER:
			return _msg + " :No such server\n";
		case ERR_NOSUCHCHANNEL:
			return _msg + ":No such channel\n";
		case ERR_CANNOTSENDTOCHAN:
			return _msg + " :Cannot send to channel\n";
		case ERR_TOOMANYCHANNELS:
			return _msg + " :You have joined too many channels\n";
		case ERR_WASNOSUCHNICK:
			return _msg + " :There was no such nickname\n";
		case ERR_TOOMANYTARGETS:
			return _msg + " :Duplicate recipients. No message delivered\n";
		case ERR_NOORIGIN:
			return ":No origin specified\n";
		case ERR_NORECIPIENT:
			return ":No recipient given (" + _msg + ")\n";
		case ERR_NOTEXTTOSEND:
			return ":No text to send\n";
		case ERR_NOTOPLEVEL:
			return _msg + " :No toplevel domain specified\n";
		case ERR_WILDTOPLEVEL:
			return _msg + " :Wildcard in toplevel domain\n";
		case ERR_UNKNOWNCOMMAND:
			return _msg + " :Unknown command\n";
		case ERR_NOMOTD:
			return ":MOTD File is missing\n";
		case ERR_NOADMININFO:
			return _msg + " :No administrative info available\n";
		// case ERR_FILEERROR:
		// 	return ":File error doing " + <file op> + " on " + <file> + "\n";
		case ERR_NONICKNAMEGIVEN:
			return " :No nickname given\n";
		case ERR_ERRONEUSNICKNAME:
			return _user + " :Erroneus nickname\n";
		case ERR_NICKNAMEINUSE:
			return _user + " :Nickname is already in use\n";
		case ERR_NICKCOLLISION:
			return _user + " :Nickname is already in use\n";
		case ERR_USERNOTINCHANNEL:
			return _user + _msg + " :They aren't on that channel\n";
		case ERR_NOTONCHANNEL:
			return _msg + " :You're not on that channel\n";
		case ERR_USERONCHANNEL:
			return _user + _msg + " :is already on channel\n";
		case ERR_NOLOGIN:
			return _user + " :User not logged in\n";
		case ERR_SUMMONDISABLED:
			return ":SUMMON has been disabled\n";
		case ERR_USERSDISABLED:
			return ":USERS has been disabled\n";
		case ERR_NOTREGISTERED:
			return ":You have not registered\n";
		case ERR_NEEDMOREPARAMS:
			return _msg + " :Not enough parameters\n";
		case ERR_ALREADYREGISTRED:
			return "You may not reregister\n";
		case ERR_NOPERMFORHOST:
			return ":Your host isn't among the privileged\n";
		case ERR_PASSWDMISMATCH:
			return ":Password incorrect\n";
		case ERR_YOUREBANNEDCREEP:
			return ":You are banned from this server";
		case ERR_KEYSET:
			return _msg + " :Channel key already set\n";
		case ERR_CHANNELISFULL:
			return _msg + " :Cannot join channel (+l)\n";
		case ERR_UNKNOWNMODE:
			return _msg + " :is unknown mode char to me\n";
		case ERR_INVITEONLYCHAN:
			return _msg + " :Cannot join channel (+i)\n";
		case ERR_BANNEDFROMCHAN:
			return _msg + " :Cannot join channel (+b)\n";
		case ERR_BADCHANNELKEY:
			return _msg + " :Cannot join channel (+k)\n";
		case ERR_NOPRIVILEGES:
			return ":Permission Denied- You're not an IRC operator\n";
		case ERR_CHANOPRIVSNEEDED:
			return _msg + " :You're not channel operator\n";
		case ERR_CANTKILLSERVER:
			return ":You cant kill a server!\n";
		case ERR_NOOPERHOST:
			return ":No O-lines for your host\n";
		case ERR_UMODEUNKNOWNFLAG:
			return ":Unknown MODE flag\n";
		case ERR_USERSDONTMATCH:
			return ":Cant change mode for other users\n";
	}
	return "type error not found\n";
}
