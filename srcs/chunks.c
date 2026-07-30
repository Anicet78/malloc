#include <malloc.h>

void*	getFirstChunk(t_zone* zone) {
	return ((void *)align((uint64_t)zone + sizeof(t_zone)));
}

void*	getTinyChunkData(t_tinychunk* chunk) {
	return ((void *)align((uint64_t)chunk + sizeof(t_tinychunk)));
}

void*	claimTinyChunk(t_zone* zone, t_tinychunk* chunk, size_t size) {
	chunk->size = size;
	chunk->allocated = true;

	zone->amount++;
	zone->reserved += align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);
	zone->used = align(sizeof(t_tinychunk) + size);

	return (getTinyChunkData(chunk));
}

t_tinychunk*	findTinySpaceInZone(size_t size, t_zone* zone) {
	if (zone->reserved + align(sizeof(t_tinychunk) + size) > zone->size)
		return (NULL);

	t_tinychunk*	current_chunk = getFirstChunk(zone);
	t_tinychunk*	zone_limit = (void *)(current_chunk) + zone->size;
	uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

	while (current_chunk < zone_limit && current_chunk->allocated == true) {
		current_chunk = (t_tinychunk *)((uint64_t)current_chunk + chunk_size);
	}

	if (current_chunk < zone_limit)
		return (current_chunk);

	return (NULL);
}

t_tinychunk*	findTinySpace(size_t size, t_zone** zone) {
	t_zone*		current_zone = malloc_singleton.tiny;

	while (current_zone) {
		t_tinychunk* found_chunk = findTinySpaceInZone(size, current_zone);

		if (found_chunk) {
			*zone = current_zone;
			return (found_chunk);
		}

		current_zone = current_zone->next;
	}

	return (NULL);
}

void*	getLargeChunkData(t_largechunk* chunk) {
	return ((void *)align((uint64_t)chunk + sizeof(t_largechunk)));
}

void*	claimLargeChunk(t_zone* zone, t_largechunk* chunk, size_t size) {
	chunk->size = size;
	chunk->allocated = true;

	zone->reserved = zone->size;
	zone->used = size;
	zone->amount++;

	return ((void *)align((uint64_t)chunk + sizeof(t_largechunk)));
}
