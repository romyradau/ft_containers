NAME = containers

CC = c++

FLAGS =  -Wall -Wextra -Werror -std=c++98

FLAGS += -g

SRC_DIR = ./src
SRC	=	$(shell find $(SRC_DIR) -name "*.cpp" -execdir echo {} ";")

OBJ_DIR	=	./obj
OBJ	=	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

DEPS	=	$(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | prep
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

prep:
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJS) $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	
re: fclean all