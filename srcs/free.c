#include "malloc.h"

void	deleteZone(t_zone* zone) {
	zone->previous->next = zone->next;
	if (zone->next)
		zone->next->previous = zone->previous;

	munmap(zone, calcPageSize(align(sizeof(t_zone)) + zone->size));
}

void	freeTiny(t_tinychunk* chunk) {
	t_zone* zone = chunk->zone;

	if (zone->amount <= 1) {
		if (malloc_singleton.tiny == zone)
			malloc_singleton.tiny = NULL;
		deleteZone(zone);
		return ;
	}

	zone->reserved -= align(sizeof(t_tinychunk)) + MALLOC_TINY_SIZE_LIMIT;
	zone->used -= getSize(chunk->size);
	zone->amount--;

	chunk->size = packVariables(0, false);
}

void	defragmentChunk(t_zone* zone, t_smallchunk* chunk) {
	if (!chunk || chunk->previous >= chunk) {
		return ;
	}

	t_smallchunk* prev_chunk = chunk->previous;

	if (isAllocated(prev_chunk->size)) {
		if (align(getSize(prev_chunk->size)) == (uint64_t)chunk)
			return ;

		t_smallchunk* new_chunk = getSmallChunkData(prev_chunk) + align(getSize(prev_chunk->size));

		prev_chunk->next = new_chunk;
		if (chunk->next)
			chunk->next->previous = new_chunk;
		else
			((t_smallchunk *)getFirstChunk(zone))->previous = new_chunk;

		new_chunk->next = chunk->next;
		new_chunk->previous = prev_chunk;
		new_chunk->zone = zone;
	}
	else {
		if (chunk->next)
			chunk->next->previous = prev_chunk;
		else
			((t_smallchunk *)getFirstChunk(zone))->previous = prev_chunk;

		prev_chunk->next = chunk->next;
	}
}

void	freeSmall(t_smallchunk* chunk) {
	t_zone* zone = chunk->zone;

	if (zone->amount <= 1) {
		if (malloc_singleton.small == zone)
			malloc_singleton.small = NULL;
		deleteZone(zone);
		return ;
	}

	zone->reserved -= align(sizeof(t_smallchunk));
	zone->used -= getSize(chunk->size);
	zone->amount--;

	defragmentChunk(zone, chunk);
	defragmentChunk(zone, chunk->next);

	chunk->size = packVariables(0, false);
}

void	freeLarge(t_largechunk* chunk) {
	t_zone* zone = chunk->zone;

	if (malloc_singleton.large == zone)
		malloc_singleton.large = NULL;
	deleteZone(zone);
}

void	free(void* ptr) {
	if (ptr == NULL)
		return ;

	uint64_t size = getSize(*(uint64_t *)(ptr - ALIGNMENT));

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		freeTiny(ptr - align(sizeof(t_tinychunk)));
	else if (size <= MALLOC_SMALL_SIZE_LIMIT)
		freeSmall(ptr - align(sizeof(t_smallchunk)));
	else
		freeLarge(ptr - align(sizeof(t_largechunk)));
}
