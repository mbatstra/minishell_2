NAME = minishell
TEST_NAME = test/unit_test

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/builtin build/env

UNPREFIXED_SRC = main.c \
	builtin/env.c \
	builtin/pwd.c \
	builtin/cd.c \
	builtin/echo.c \
	builtin/exit.c \
	builtin/export.c \
	builtin/unset.c \
	env/env.c \
	lexer.c

TEST_SRC = test/test.c

OBJ = $(addprefix $(BUILD_DIR), $(UNPREFIXED_SRC:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(UNPREFIXED_SRC))

INC = inc/
TEST_INC = test/criterion--git/include

#FLAGS = -fsanitize=address -g 
FLAGS = -Wall -Wextra -Werror 

LIB = lib/
LIBFT = lib/libft/libft.a
CRITERION = test/criterion--git/libcriterion.dylib

all: $(LIBFT) $(NAME)
test: $(TEST_NAME)

$(LIBFT):
	$(MAKE) -C $(LIB)libft/ WITH_BONUS=1

$(NAME): $(OBJ) $(INC)*
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -I$(INC) -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@

$(TEST_NAME): $(LIBFT) $(TEST_SRC) $(filter-out main.c, $(SRC))
	$(CC) $(TEST_SRC) $(LIBFT) $(filter-out src/main.c, $(SRC)) $(CRITERION) -I$(INC) -I$(TEST_INC) -o $(TEST_NAME) 

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
	all clean fclean re test
