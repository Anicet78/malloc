#include "malloc.h"

void*	shrinkTiny(t_tinychunk* chunk, size_t size) {
	chunk->size = size;
	return (chunk);
}

void*	shrinkSmall(t_smallchunk* chunk, size_t size) {
	chunk->size = size;
	return (chunk);
}

void*	shrinkLarge(t_largechunk* chunk, size_t size) {
	chunk->size = size;
	return (chunk);
}

void*	shrink(void *ptr, size_t size, size_t old_size) {
	if (old_size <= MALLOC_TINY_SIZE_LIMIT)
		return (shrinkTiny(ptr - align(sizeof(t_tinychunk)), size));
	else if (old_size <= MALLOC_SMALL_SIZE_LIMIT)
		return (shrinkSmall(ptr - align(sizeof(t_smallchunk)), size));
	return (shrinkLarge(ptr - align(sizeof(t_largechunk)), size));
}

void*	growTiny(t_tinychunk* chunk, size_t size, size_t old_size) {
	if (size > MALLOC_TINY_SIZE_LIMIT) {
		void* newAlloc = malloc(size);
		if (newAlloc)
			ft_memcpy(newAlloc, getTinyChunkData(chunk), old_size);
		free(chunk);
		return ;
	}

	chunk->size = size;
	return (chunk);
}

void*	growSmall(t_smallchunk* chunk, size_t size, size_t old_size) {
	if ((size > MALLOC_SMALL_SIZE_LIMIT) || (chunk->next && chunk->next - (uint64_t)getSmallChunkData(chunk) < size)) {
		void* newAlloc = malloc(size);
		if (newAlloc)
			ft_memcpy(newAlloc, getSmallChunkData(chunk), old_size);
		free(getSmallChunkData(chunk));
		return (newAlloc);
	}

	if (!chunk->next) {
		t_zone* zone = searchZone(chunk, malloc_singleton.small);
		if (!zone)
			return (free(getSmallChunkData(chunk)), NULL);

		if ((getFirstChunk(zone) + zone->size) - (uint64_t)getSmallChunkData(chunk) < size) {
			void* newAlloc = malloc(size);
			if (newAlloc)
				ft_memcpy(newAlloc, getSmallChunkData(chunk), old_size);
			free(getSmallChunkData(chunk));
			return (newAlloc);
		}
	}

	chunk->size = size;
	return (chunk);
}

void*	growLarge(t_largechunk* chunk, size_t size) {
	return (chunk);
}

void*	grow(void *ptr, size_t size, size_t old_size) {
	if (old_size <= MALLOC_TINY_SIZE_LIMIT)
		return (growTiny(ptr - align(sizeof(t_tinychunk)), size, old_size));
	else if (old_size <= MALLOC_SMALL_SIZE_LIMIT)
		return (growSmall(ptr - align(sizeof(t_smallchunk)), size, old_size));
	return (growLarge(ptr - align(sizeof(t_largechunk)), size, old_size));
}

void	*realloc(void *ptr, size_t size) {
	if (ptr == NULL)
		return (malloc(size));

	if (size == 0)
		return (free(ptr), NULL);

	uint64_t og_size = *(uint64_t *)(ptr - ALIGNMENT);
	if (size == og_size)
		return ;

	if (size < og_size)
		return (shrink(ptr, size, og_size));
	else
		return (grow(ptr, size, og_size));
}