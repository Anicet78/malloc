/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:54:10 by agruet            #+#    #+#             */
/*   Updated: 2026/03/20 19:03:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>

// Bases
# define BASE_10 "0123456789"
# define BASE_16L "0123456789abcdef"
# define BASE_16U "0123456789ABCDEF"

// libc functions
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrcmp(const char *s1, const char *s2);
int		ft_strrncmp(const char *s1, const char *s2, int n);
int		ft_str_equals(const char *s1, const char *s2);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strlstr(const char *big, const char *little, size_t len);
char	*ft_strrstr(const char *big, const char *little);
int		ft_strstr_tab(char **tab, char *str);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *nptr);
double	ft_atof(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *old_ptr, size_t size, size_t old_size);
char	*ft_strdup(const char *s);

// additional functions
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	*free_tab(char **tab, int nb);
int		count_words(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_ltoa(long n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
size_t	tab_len(char **tab);
void	shift_elem_up(char **tab, char *elem);
void	shift_elem_down(char **tab, char *elem);

// maths
double	q_rsqrt(double number);
int		ft_max(int a, int b);
int		ft_min(int a, int b);

// printf
# define PRINTF_BUFF_SIZE 1024
# define AVAILABLE_PRINTF_CONVERT "cspdiuxXf%"

typedef enum printf_flags
{
	INVALID_FLAG = -1,
	NO_FLAGS = 0,
	LEFT_JUSTIFY = 1 << 0,
	PAD_ZEROS = 1 << 1,
	PRECISION = 1 << 2,
	ALTERNATIVE_FORM = 1 << 3,
	SHOW_SIGN = 1 << 4,
	SPACE_POSITIVE = 1 << 5,
	LONG_NUMBER = 1 << 6
}	t_pflags;

typedef struct s_printf
{
	va_list		ap;
	char		*str;
	char		buff[PRINTF_BUFF_SIZE];
	size_t		buff_size;
	size_t		buff_pos;
	size_t		current;
	size_t		str_len;
	int			fd;
	int			len;
	t_pflags	flags;
	int			padding;
	int			precision;
}	t_printf;

int		ft_printf(const char *s, ...);
int		ft_fprintf(int fd, const char *s, ...);
int		write_to_buff(t_printf *ft_print, char *to_write, size_t size);
int		flush_printf(t_printf *ft_print);
int		parse_flags(t_printf *ft_print, char *str, size_t current);
void	start_conversion(t_printf *ft_print, char *str, va_list ap);
void	write_char(t_printf *ft_print, int c);
void	write_str(t_printf *ft_print, char *str);
void	write_ptr(t_printf *ft_print, unsigned long long ptr);
void	write_int(t_printf *ft_print, int n, char *base, int base_len);
void	write_uint(t_printf *ft_print, unsigned int nb, char *base, int b_len);
void	write_long(t_printf *ft_print, long n, char *base, int base_len);
void	write_ulong(t_printf *ft_print, unsigned long nb, char *base, int len);
void	write_double(t_printf *ft_print, double n);
int		calc_str_size(t_printf *ft_print, char *str);
int		calc_int_size(t_printf *ft_print, int n, int base_len);
int		calc_uint_size(t_printf *ft_print, unsigned int nb, int base_len);
int		calc_long_size(t_printf *ft_print, long nb, int base_len);
int		calc_ulong_size(t_printf *ft_print, unsigned long nb, int base_len);
int		calc_llong_size(t_printf *ft_print, unsigned long long ptr);
int		calc_double_size(t_printf *ft_print, double n, int precision, bool dot);
int		apply_numeric_flag(t_printf *ft_print, int len,
			char *base, bool is_neg);
int		write_padding(t_printf *ft_print, int padding, int c);
int		write_sharp(t_printf *ft_print, char *base);
int		write_sign(t_printf *ft_print, bool is_neg);
int		write_null(t_printf *ft_print);

// linked lists
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	free_content(void *content);
void	void_content(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	lst_remove_node(t_list **lst, t_list *node, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstprint(t_list *lst);
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstfirst(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);
void	ft_dlst_top(t_dlist **lst);
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));
void	dlst_remove_node(t_dlist **lst, t_dlist *node, void (*del)(void*));
void	ft_dlst_shift_up(t_dlist **lst, t_dlist *node);
void	ft_dlst_shift_down(t_dlist **lst, t_dlist *node);
t_dlist	*ft_strstr_dlst(t_dlist *lst, char *str);
void	ft_dlstprint(t_dlist *lst);

// maps
typedef struct s_map
{
	char			*key;
	char			*value;
	struct s_map	*next;
}	t_map;

t_map	*newmap(char *key, char *value);
t_map	*ft_maplast(t_map *map);
void	ft_addmap(t_map **map, t_map *new);
void	ft_mapclear(t_map **map);
void	map_remove_node(t_map **map, t_map *node);
size_t	ft_mapsize(t_map *map);

// arena
# define CHUNK_SIZE 4194304

typedef struct s_chunk	t_chunk;

struct s_chunk
{
	t_chunk		*next;
	size_t		count;
	size_t		capacity;
	uintptr_t	data[];
};

typedef struct s_arena
{
	t_chunk	*begin;
	t_chunk	*end;
	size_t	size;
	int		freed;
}	t_arena;

t_arena	*arena_init(size_t size);
t_chunk	*region_create(size_t capacity);
void	*arena_regions_free(t_arena *arena);
void	*arena_alloc(size_t size, t_arena *arena);
void	*arena_calloc(t_arena *arena, size_t size);
void	*arena_realloc(t_arena *arena, void *old_ptr,
			size_t size, size_t old_size);
void	clear_arena(t_arena **arena);
void	reset_arena(t_arena **arena);

// memory
void	*ft_print_memory(void *addr, size_t size);

// readfile
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif
