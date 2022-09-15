NAME = minishell

SRC_DIR = src/
BUILD_DIR = build/

UNPREFIXED_SRC = main.c \
	builtins.c \
	builtin_cd.c \
	env.c \
	env_util.c

OBJ = $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

INC = inc/

FLAGS = -Wall -Wextra -Werror

LIB = lib/
LIBFT = lib/libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB)libft/

$(NAME): $(OBJ) $(INC)*
	$(CC) $(OBJ) $(LIBFT) -I$(INC) -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re
