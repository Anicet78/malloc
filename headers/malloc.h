#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include "color.h"
# include <sys/mman.h>
# include <stdalign.h>

# define MALLOC_PAGE_SIZE sysconf(_SC_PAGESIZE)
# define ALIGNMENT alignof(max_align_t)

# define MALLOC_TINY_SIZE_LIMIT  64
# define MALLOC_TINY_ZONE_SIZE   32768

# define MALLOC_SMALL_SIZE_LIMIT 16384
# define MALLOC_SMALL_ZONE_SIZE  65536

typedef enum page_size {
	TINY,
	SMALL,
	LARGE
}	t_page_size;

typedef struct s_zone	t_zone;
struct s_zone
{
	t_zone*		next;
	t_zone*		previous;
	uint64_t	size;
	uint64_t	reserved;
	uint64_t	used;
	uint64_t	amount;
	t_page_size	page_size;
};

typedef struct s_tinychunk	t_tinychunk;
struct s_tinychunk
{
	uint64_t	size;
	t_zone*		zone;
};

typedef struct s_smallchunk	t_smallchunk;
struct s_smallchunk
{
	t_smallchunk*	next;
	t_smallchunk*	previous;
	uint64_t		size;
	t_zone*			zone;
};

typedef struct s_largechunk	t_largechunk;
struct s_largechunk
{
	uint64_t	size;
	t_zone*		zone;
};

typedef struct s_allocator
{
	t_zone*		tiny;
	t_zone*		small;
	t_zone*		large;
	uint64_t	allocations;
	uint64_t	free;
}	t_allocator;

extern t_allocator malloc_singleton;

// Page
void*	newRawPage(size_t size);
size_t	align(size_t size);
size_t	calcPageSize(size_t size);

// Zone
t_zone*			newZone(size_t size);
void*			getFirstChunk(t_zone* zone);
void*			getZoneEnd(t_zone* zone);

// Chunk
bool			isAllocated(uint64_t size);
uint64_t		getSize(uint64_t size);
uint64_t		packVariables(uint64_t size, bool allocated);
uint64_t		setAllocated(uint64_t size, bool allocated);
uint64_t		setSize(uint64_t size, uint64_t value);
void*			getTinyChunkData(t_tinychunk* chunk);
void*			getSmallChunkData(t_smallchunk* chunk);
void*			getLargeChunkData(t_largechunk* chunk);
t_tinychunk*	findTinySpaceInZone(size_t size, t_zone* zone);
t_tinychunk*	findTinySpace(size_t size, t_zone** zone);
t_smallchunk*	findSmallSpaceInZone(size_t size, t_zone* zone);
t_smallchunk*	findSmallSpace(size_t size, t_zone** zone);
void*			claimTinyChunk(t_zone* zone, t_tinychunk* chunk, size_t size);
void*			claimSmallChunk(t_zone* zone, t_smallchunk* chunk, size_t size);
void*			claimLargeChunk(t_zone* zone, t_largechunk* chunk, size_t size);

void	*malloc(size_t size);
void	*calloc(size_t nmemb, size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void* ptr);

void	show_alloc_mem();
void	show_alloc_mem_ex();

#endif // !FT_MALLOC_H
