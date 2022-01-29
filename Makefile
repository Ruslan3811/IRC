NAME= ircserv

SOURCEFILES= main.cpp Server.cpp Cmd.cpp User.cpp Message.cpp dop_function.cpp Exception.cpp Channel.cpp

SOURCEFOLDER= srcs/

OSOURCEFOLDER= .objects/

INCLUDEFOLDER= include/

SOURCE= $(addprefix $(SOURCEFOLDER), $(SOURCEFILES))

OSOURCE= $(addprefix $(OSOURCEFOLDER), $(SOURCEFILES:.cpp=.o))

all: $(NAME)

$(OSOURCEFOLDER)%.o: $(SOURCEFOLDER)%.cpp
	mkdir -p $(OSOURCEFOLDER)
	clang++ -Wall -Werror -Wextra -c $< -o $@ -std=c++98 -I $(INCLUDEFOLDER)
	
$(NAME): $(OSOURCE)
	clang++ $(OSOURCE) -o $(NAME)

clean:
	rm -rf $(OSOURCEFOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all dir