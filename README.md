<h1>IRC-server</h1>
IRC (Internet Relay Chat) – устаревший протокол прикладного уровня для обмена сообщениями в режиме реального времени. Разработан в 1988 году и предназначен для группового общения, также позволяет общаться через личные сообщения и обмениваться файлами. Несмотря на устарелость, на основе IRC в дальнейшем разработано множество мессенджеров, такие как: ICQ, Skype, Discord, Telegram, Slack, etc...

Проект представляет собой IRC-сервер, написанный на основе стандарта [rfc1459](https://datatracker.ietf.org/doc/html/rfc1459).

<h2>Установка</h2>
git clone\n
cd IRC/\n
make\n
Запуск сервера:\n
./ircserv 6667 secretpassword\n
Запуск клиента:\n
"nc localhost 6667"\n
