NAME = ircserv

SOURCE = main.cpp Server.cpp Cmd.cpp User.cpp Message.cpp dop_func.cpp

OBJ_DIR = .obj

HDR = Server.hpp Errors.hpp User.hpp Message.hpp exeption.hpp

FLAGS = --std=c++11

OBJ = $(addprefix $(OBJ_DIR)/,$(SOURCE:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(SOURCE) -o $(NAME)

$(OBJ_DIR)/%.o:%.cpp $(HDR)
	sudo mkdir -p $(OBJ_DIR)
	clang++ -c $(FLAGS) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
