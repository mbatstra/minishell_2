NAME = minishell

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/builtin build/env

UNPREFIXED_SRC = main.c \
	builtin/env.c \
	builtin/pwd.c \
	builtin/cd.c \
	builtin/echo.c \
	builtin/exit.c \
	env/env.c \
	env/env_util.c

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

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

$(BUILD_SUBDIRS):
	mkdir $@

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIB)libft/

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB)libft/

re: fclean all

.PHONY:
	all clean fclean re
