NAME = ircserv

SOURCE = main.cpp Server.cpp

OBJ_DIR = .obj

HDR = Server.hpp

FLAGS = -Wall -Wextra -Werror --std=c++98

OBJ = $(addprefix $(OBJ_DIR)/,$(SOURCE:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@clang++ $(SOURCE) -o $(NAME)

$(OBJ_DIR)/%.o:%.cpp $(HDR)
	@mkdir -p $(OBJ_DIR)
	@clang++ -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
