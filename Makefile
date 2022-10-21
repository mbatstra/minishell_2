NAME = minishell
TEST_NAME = test/unit_test

SRC_DIR = src/
BUILD_DIR = build/
BUILD_SUBDIRS = build/builtin build/env build/expand build/lexer build/parse build/exec

UNPREFIXED_SRC = main.c \
	builtin/env.c \
	builtin/pwd.c \
	builtin/cd.c \
	builtin/echo.c \
	builtin/exit.c \
	builtin/export.c \
	builtin/unset.c \
	env/env.c \
	expand/rel_path.c \
	expand/parent_dir.c \
	lexer/lexer.c \
	lexer/lexer_error.c \
	lexer/lexer_utils.c \
	lexer/tokenize_word.c \
	lexer/tokenize_operator.c \
	parse/parse.c \
	parse/parse_util.c \
	parse/parse_redir.c \
	parse/parse_word.c \
	exec/execute.c\
	exec/heredoc.c\
	exec/protect.c\
	exec/command.c\
	exec/builtin.c\
	exec/fork.c\
	exec/redirection.c\

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

RESET		=	"\033[0m"
RED			=	"\033[0;31m"
GREEN		=	"\033[1;32m"
YELLOW		=	"\033[0;33m"

all: $(LIBFT) $(BUILD_DIR) $(NAME)
test: $(TEST_NAME)

$(LIBFT):
	@$(MAKE) -C $(LIB)libft/ WITH_BONUS=1

$(BUILD_DIR):
	@mkdir $@

$(BUILD_SUBDIRS):
	@mkdir $@

$(NAME): $(OBJ) $(INC)*
	@echo $(YELLOW)"Object files created...!"$(RESET)
	@echo $(GREEN)"Minishell is ready!\n"$(RESET)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -lreadline -I$(INC) -o $(NAME)
	@echo $(GREEN)"               *------------------------------------------------------------------------------------------------------*"$(RESET)
	@echo $(GREEN)"               | *--------------------------------------------------------------------------------------------------* |"$(RESET)
	@echo $(GREEN)"               | |                  __  __    _____    _____   _    _   ______   _        _                         | |"$(RESET)
	@echo $(GREEN)"               | |                 |  \/  |  / ____|  / ____| | |  | | |  ____| | |      | |                        | |"$(RESET)
	@echo $(GREEN)"               | |                 | \  / | | |      | (___   | |__| | | |__    | |      | |                        | |"$(RESET)
	@echo $(GREEN)"               | |                 | |\/| | | |       \___ \  |  __  | |  __|   | |      | |                        | |"$(RESET)
	@echo $(GREEN)"               | |                 | |  | | | |____   ____) | | |  | | | |____  | |____  | |____                    | |"$(RESET)
	@echo $(GREEN)"               | |                 |_|  |_|  \_____| |_____/  |_|  |_| |______| |______| |______|                   | |"$(RESET)
	@echo $(GREEN)"               | |                                                                                                  | |"$(RESET)
	@echo $(GREEN)"               | *--------------------------------------------------------------------------------------------------* |"$(RESET)
	@echo $(GREEN)"               *------------------------------------------------------------------------------------------------------*\n"$(RESET)


$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	@printf $(YELLOW)"%-33.33s\r"$(RESET) $@
	@$(CC) $(FLAGS) -I$(INC) -c $< -o $@

$(TEST_NAME): $(LIBFT) $(TEST_SRC) $(filter-out main.c, $(SRC))
	$(CC) $(TEST_SRC) $(LIBFT) $(filter-out src/main.c, $(SRC)) $(CRITERION) -I$(INC) -I$(TEST_INC) -o $(TEST_NAME) 

clean:
	@rm -rdf $(BUILD_DIR)
	@$(MAKE) clean -C $(LIB)libft/
	@echo $(RED)"Object files deleted"$(RESET)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB)libft/
	@echo $(RED)"$(NAME) executable deleted"$(RESET)

re: fclean all

.PHONY:
	all clean fclean re test
