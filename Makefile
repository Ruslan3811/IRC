NAME = ircserv

SOURCE = main.cpp Server.cpp Cmd.cpp User.cpp Message.cpp dop_func.cpp Exeption.cpp

OBJ_DIR = .obj

HDR = Server.hpp Errors.hpp User.hpp Message.hpp Exeption.hpp Cmd.hpp

FLAGS = -Wall -Wextra -Werror --std=c++98

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
