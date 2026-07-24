#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <stdalign.h>

# define MALLOC_REQUIRED_SIZE sysconf(_SC_PAGESIZE)
# define ALIGNMENT alignof(max_align_t)

# define MALLOC_TINY_SIZE_LIMIT 64
# define MALLOC_TINY_ZONE_SIZE 32768

# define MALLOC_SMALL_SIZE_LIMIT 16384
# define MALLOC_SMALL_ZONE_SIZE 32768

typedef struct s_tinychunk	t_tinychunk;
struct s_tinychunk
{
	uint8_t	size;
	bool	allocated;
};

typedef struct s_smallchunk	t_smallchunk;
struct s_smallchunk
{
	t_zone*		next;
	t_zone*		previous;
	uint64_t	size;
	bool		allocated;
};

typedef struct s_largechunk	t_largechunk;
struct s_largechunk
{
	uint64_t	size;
	bool		allocated;
};

typedef struct s_zone	t_zone;
struct s_zone
{
	t_zone*		next;
	t_zone*		previous;
	uint64_t	size;
	uint64_t	used;
	uint64_t	amount;
};

typedef struct s_allocator
{
	t_zone*	tiny;
	t_zone*	small;
	t_zone*	large;
}	t_allocator;

extern volatile t_allocator malloc_singleton;

void*		newRawPage(size_t size);

size_t	align(size_t size);
void*	getFirstChunk(t_zone* zone);

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);

void	show_alloc_mem();
void	show_alloc_mem_ex();

#endif // !FT_MALLOC_H