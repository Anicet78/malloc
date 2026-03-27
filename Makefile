CC			= cc
CFLAGS		= -Wall -Werror -Wextra -ggdb -fPIC

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

HEADERS		= headers
SRC_DIR		= srcs
OBJ_DIR		= objs

CFLAGS		+= -I$(HEADERS)

SRC			= malloc.c utils.c
OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

TEST_SRC	= test.c
TEST_OBJ	= $(patsubst %.c, $(OBJ_DIR)/%.o, $(TEST_SRC))
TEST_NAME	= test_bin

ifeq (${HOSTTYPE},)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_${HOSTTYPE}.so

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -shared $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lft_malloc_${HOSTTYPE} -Wl,-rpath,. -ggdb -o test_bin

clean:
	@printf "\e[1;36mCleaning files\e[0m\n"
	@make clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all test clean fclean re
