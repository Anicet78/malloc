#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>

# define MALLOC_REQUIRED_SIZE 512

typedef struct s_chunk	t_chunk;

struct s_chunk
{
	t_chunk*	next;
	size_t		count;
	size_t		capacity;
	uint8_t*	data;
};

typedef struct s_allocator
{
	t_chunk*	begin;
}	t_allocator;

extern volatile t_allocator* malloc_singleton;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	show_alloc_mem();
void	show_alloc_mem_ex();

#endif // !FT_MALLOC_H