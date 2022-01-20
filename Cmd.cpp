#include "Server.hpp"
#include "cmd.hpp"
#include "exeption.hpp"


Command::Command(const Message & msg,const User & user) : _msg(msg), _user(user) {}
void Command::cmdPass()
{
	std::string password = _msg.getParams().front();
    if (!_user.IsTrueLength(password))
		throw errorRequest(_msg, _user, ERR_NEEDMOREPARAMS);
	else if (_user.isAlreadyRegistered())
		throw errorRequest(_msg, _user, ERR_ALREADYREGISTRED);
	_user.setPassword(password);
}

void Command::cmdUser()
{
	std::string realname = _msg.getTrailing();

	if (_msg.getParams().size() != 3 || realname.length() == 1)
		throw errorRequest(_msg, _user, ERR_NEEDMOREPARAMS);
	else if (_user.isAlreadyRegistered())
		throw errorRequest(_msg, _user, ERR_ALREADYREGISTRED);
	_user.setUserName(_msg.getParams()[0]);
	_user.setUserRealName(_msg.getTrailing().erase(0, 1));
}


//доделать изменение ника

//нужна функция определяющая в сети пользователь или нет
// int Server::cmdNick(Message &_msg, _user &_user)
// {
// //_msg->cmd и _msg->params - не распарсенные
//     std::vector<_user *>::iterator begin = this->get_users().begin();
// 	std::vector<_user *>::iterator end = this->get_users().end();
//     std::string nickname = "";
//     if (_msg.getParams().size())
//     {
//         if (_user.getNickName().length() > 0)
//         { 
//             std::cout << "this _user already has got nickname";
//             return (0);
//         }
//         for (;begin != end;++begin)
//         {
//             // std::cout << _msg.getParams().front();
//             if (_msg.getParams().front() == (*begin)->getNickName() && (*begin)->isActive_user())
//             {
//                 std::cout << "ERR_NICKNAMEINUSE" << std::endl;
//                 return (0);
//                 // return sendErr(_msg, _user,  ERR_NICKNAMEINUSE);
//             }
//         }
//         nickname = _msg.getParams().front();
//     }
//     else if (_msg.getTrailing().length() == 0 && _msg.getParams().front().length() == 0)
//     {
//         std::cout << "ERR_NONICKNAMEGIVEN" << std::endl;
//         return (0);
//     }


//     for (size_t c = 0;  c < nickname.length(); ++c)
//     {
//         if (nickname[c] != ' ' && (nickname[c] < '0' || nickname[c] > '9') && (nickname[c] < 'a' || nickname[c] > 'z') && (nickname[c] < 'A' || nickname[c] > 'Z'))
//         {
//             std::cout << "ERR_ERRONEUSNICKNAME" << std::endl;
//             return (0);
//             // return sendErr(_msg, _user, ERR_ERRONEUSNICKNAME);
//         }    
//     }

//     std::string trailing = _msg.getTrailing();
    
//     if (_msg.getTrailing().length() > 0 && nickname.length() == 0)
//     {
//         trailing.erase(0, 1);
//         std::string old_nick = trailing.substr(0, trailing.find(" "));
//         trailing.erase(0, trailing.find(" "));
//         int i = 0;
//         for (; trailing[i] == ' '; ++i){}
//         trailing.erase(0, i);
//         i = 0;
//         for (; trailing[i] != ' ' && trailing[i]; ++i){}
//         std::string nick = trailing.substr(0, i);
//         trailing.erase(0, i);
//         i = 0;
//         for (; trailing[i] == ' '; ++i){}
//         trailing.erase(0, i);
//         nickname = trailing;    
//     }
//     _user.set_userName(nickname);
// 	return (0);
// }

