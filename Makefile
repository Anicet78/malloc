CC			= cc
CFLAGS		= -Wall -Werror -Wextra -ggdb

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

HEADERS		= headers
SRC_DIR		= srcs
OBJ_DIR		= objs

CFLAGS		+= -I$(HEADERS)

SRC			= malloc.c
OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

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

clean:
	@printf "\e[1;36mCleaning files\e[0m\n"
	@make clean -sC $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -sC $(LIBFT_DIR)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
