#include "malloc.h"

void*	shrinkTiny(t_tinychunk* chunk, size_t size, size_t old_size) {
	chunk->size = setSize(chunk->size, size);
	chunk->zone->used -= old_size - size;
	return (getTinyChunkData(chunk));
}

void*	shrinkSmall(t_smallchunk* chunk, size_t size, size_t old_size) {
	chunk->size = setSize(chunk->size, size);
	chunk->zone->reserved = chunk->zone->reserved - align(old_size) + align(size);
	chunk->zone->used -= old_size - size;
	return (getSmallChunkData(chunk));
}

void*	shrinkLarge(t_largechunk* chunk, size_t size) {
	chunk->size = setSize(chunk->size, size);
	chunk->zone->used = size;
	return (getLargeChunkData(chunk));
}

void*	shrink(void *ptr, size_t size, size_t old_size) {
	if (old_size <= MALLOC_TINY_SIZE_LIMIT)
		return (shrinkTiny(ptr - align(sizeof(t_tinychunk)), size, old_size));
	else if (old_size <= MALLOC_SMALL_SIZE_LIMIT)
		return (shrinkSmall(ptr - align(sizeof(t_smallchunk)), size, old_size));
	return (shrinkLarge(ptr - align(sizeof(t_largechunk)), size));
}

void*	growTiny(t_tinychunk* chunk, size_t size, size_t old_size) {
	if (size > MALLOC_TINY_SIZE_LIMIT) {
		void* newAlloc = malloc(size);
		if (newAlloc)
			ft_memcpy(newAlloc, getTinyChunkData(chunk), old_size);
		free(getTinyChunkData(chunk));
		return (newAlloc);
	}

	chunk->size = setSize(chunk->size, size);
	chunk->zone->used += size - old_size;
	return (getTinyChunkData(chunk));
}

void*	growSmall(t_smallchunk* chunk, size_t size, size_t old_size) {
	if ((size > MALLOC_SMALL_SIZE_LIMIT) || (chunk->next && (uint64_t)chunk->next - (uint64_t)getSmallChunkData(chunk) < size)) {
		void* newAlloc = malloc(size);
		if (newAlloc)
			ft_memcpy(newAlloc, getSmallChunkData(chunk), old_size);
		free(getSmallChunkData(chunk));
		return (newAlloc);
	}

	if (!chunk->next) {
		t_zone* zone = chunk->zone;

		if (((uint64_t)getFirstChunk(zone) + zone->size) - (uint64_t)getSmallChunkData(chunk) < size) {
			void* newAlloc = malloc(size);
			if (newAlloc)
				ft_memcpy(newAlloc, getSmallChunkData(chunk), old_size);
			free(getSmallChunkData(chunk));
			return (newAlloc);
		}
	}

	chunk->size = setSize(chunk->size, size);
	chunk->zone->reserved = chunk->zone->reserved - align(old_size) + align(size);
	chunk->zone->used += size - old_size;
	return (getSmallChunkData(chunk));
}

void*	growLarge(t_largechunk* chunk, size_t size, size_t old_size) {
	t_zone* zone = chunk->zone;

	if (size > zone->size) {
		void* newAlloc = malloc(size * 2);
		if (newAlloc)
			ft_memcpy(newAlloc, getLargeChunkData(chunk), old_size);
		free(getLargeChunkData(chunk));

		t_largechunk* newChunk = newAlloc - align(sizeof(t_largechunk));
		newChunk->size = setSize(newChunk->size, size);
		newChunk->zone->used = size;

		return (newAlloc);
	}

	chunk->size = setSize(chunk->size, size);
	chunk->zone->used = size;
	return (getLargeChunkData(chunk));
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

	uint64_t og_size = getSize(*(uint64_t *)(ptr - ALIGNMENT));
	if (size == og_size)
		return (ptr);

	if (size < og_size)
		return (shrink(ptr, size, og_size));
	else
		return (grow(ptr, size, og_size));
}
