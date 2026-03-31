#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>

# define MALLOC_REQUIRED_SIZE 4096

typedef enum alloc_status
{
	ALLOCATED,
	FREE
}	alloc_status;

typedef struct s_chunk	t_chunk;
struct s_chunk
{
	alloc_status	status;
	void*			data;
	size_t			size;
	t_chunk*		next;
	t_chunk*		previous;
};

typedef struct s_page	t_page;
struct s_page
{
	t_chunk*	chunks;
	void*		ptr;
	size_t		alloc_amount;
	t_page*		next;
	t_page*		previous;
};

typedef struct s_allocator
{
	t_page*		pages;
	t_chunk*	chunk_ptr;
	t_page*		page_ptr;
	t_page*		page_end;
}	t_allocator;

extern volatile t_allocator* malloc_singleton;

void*		newRawPage(size_t size);
t_page*		newPage(size_t size);
t_chunk*	findSpace(t_page* page, size_t size);
void*		newChunk(t_page* page, size_t size, t_chunk* free_chunk);

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	show_alloc_mem();
void	show_alloc_mem_ex();

#endif // !FT_MALLOC_H