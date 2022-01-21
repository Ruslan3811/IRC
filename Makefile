NAME = ircserv

SOURCE = main.cpp Server.cpp Cmd.cpp User.cpp Message.cpp dop_func.cpp Exсeption.cpp

OBJ_DIR = .obj

HDR = Server.hpp Errors.hpp User.hpp Message.hpp Exсeption.hpp Cmd.hpp

FLAGS =  --std=c++98
# -Werror-Wall -Wextra 
OBJ = $(addprefix $(OBJ_DIR)/, $(SOURCE:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(OBJ_DIR)
	clang++ -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
