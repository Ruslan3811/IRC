NAME = ircserv

SOURCE = main.cpp Server.cpp Cmd.cpp Errors.cpp User.cpp Message.cpp dop_func.cpp

OBJ_DIR = .obj

HDR = Server.hpp Errors.hpp User.hpp Message.hpp

FLAGS = -Wall -Wextra -Werror --std=c++98

OBJ = $(addprefix $(OBJ_DIR)/,$(SOURCE:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(SOURCE) -o $(NAME)

$(OBJ_DIR)/%.o:%.cpp $(HDR)
	@mkdir -p $(OBJ_DIR)
	@g++ -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
