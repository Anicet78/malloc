AR			= ar rcs
CC			= cc
CFLAGS		= -ggdb -Wall -Werror -Wextra -fPIC

HEADERS		= ../headers
SRC_DIR		= srcs
OBJ_DIR		= objs

CFLAGS		+= -I$(HEADERS)

SRC			=	libc/ft_atof.c					\
				libc/ft_atoi.c					\
				libc/ft_atol.c					\
				libc/ft_bzero.c					\
				libc/ft_calloc.c				\
				libc/ft_isalnum.c				\
				libc/ft_isalpha.c				\
				libc/ft_isascii.c				\
				libc/ft_isdigit.c				\
				libc/ft_isprint.c				\
				libc/ft_itoa.c					\
				libc/ft_ltoa.c					\
				libc/ft_memchr.c				\
				libc/ft_memcmp.c				\
				libc/ft_memcpy.c				\
				libc/ft_memmove.c				\
				libc/ft_memset.c				\
				libc/ft_putchar_fd.c			\
				libc/ft_putendl_fd.c			\
				libc/ft_putnbr_fd.c				\
				libc/ft_putstr_fd.c				\
				libc/ft_realloc.c				\
				libc/ft_shift_elem.c			\
				libc/ft_split.c					\
				libc/ft_str_equals.c			\
				libc/ft_strchr.c				\
				libc/ft_strcmp.c				\
				libc/ft_strdup.c				\
				libc/ft_striteri.c				\
				libc/ft_strjoin.c				\
				libc/ft_strlcat.c				\
				libc/ft_strlcpy.c				\
				libc/ft_strlen.c				\
				libc/ft_strlstr.c				\
				libc/ft_strrstr.c				\
				libc/ft_strmapi.c				\
				libc/ft_strncmp.c				\
				libc/ft_strnstr.c				\
				libc/ft_strrchr.c				\
				libc/ft_strrncmp.c				\
				libc/ft_strrcmp.c				\
				libc/ft_strstr_tab.c			\
				libc/ft_strtrim.c				\
				libc/ft_substr.c				\
				libc/ft_tolower.c				\
				libc/ft_toupper.c				\
				libc/tab_len.c					\
				data/dlst/ft_dlst_shift.c		\
				data/dlst/ft_dlst_top.c			\
				data/dlst/ft_dlstadd_back.c		\
				data/dlst/ft_dlstadd_front.c	\
				data/dlst/ft_dlstclear.c		\
				data/dlst/ft_dlstdelone.c		\
				data/dlst/ft_dlstfirst.c		\
				data/dlst/ft_dlstlast.c			\
				data/dlst/ft_dlstnew.c			\
				data/dlst/ft_dlstprint.c		\
				data/dlst/ft_dlstremove_node.c	\
				data/dlst/ft_strstr_dlst.c		\
				data/lst/ft_lstadd_back.c		\
				data/lst/ft_lstadd_front.c		\
				data/lst/ft_lstclear.c			\
				data/lst/ft_lstdelone.c			\
				data/lst/ft_lstfree_content.c	\
				data/lst/ft_lstiter.c			\
				data/lst/ft_lstlast.c			\
				data/lst/ft_lstmap.c			\
				data/lst/ft_lstnew.c			\
				data/lst/ft_lstprint.c			\
				data/lst/ft_lstremove_node.c	\
				data/lst/ft_lstsize.c			\
				data/lst/ft_lstvoid_content.c	\
				data/memory/print_memory.c		\
				data/maps/ft_maps.c				\
				data/maps/ft_maps2.c			\
				printf/buffer.c					\
				printf/calc_padding.c			\
				printf/calc_padding2.c			\
				printf/convertion.c				\
				printf/ft_fprintf.c				\
				printf/ft_printf.c				\
				printf/parse_flags.c			\
				printf/write_converts.c			\
				printf/write_converts2.c		\
				printf/write_flags.c			\
				readfile/get_next_line.c		\
				maths/ft_max.c					\
				maths/ft_min.c					\
				maths/q_rsqrt.c					\

OBJ			= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

NAME		= libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	@printf "\r\e[2K\e[1;32mLibft Compiled\e[0m\n"

INDEX=0
TOTAL=$(words $(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(eval INDEX=$(shell echo $$(($(INDEX)+1))))
	@printf "\r\e[2K\e[1;32mCompiling [%d/%d] %s\e[0m" $(INDEX) $(TOTAL) $(notdir $<)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
