#include <malloc.h>

void*	getFirstChunk(t_zone* zone) {
	return ((void *)align((uint64_t)zone + sizeof(t_zone)));
}

bool	isAllocated(uint64_t size) {
	return (size & 1);
}

uint64_t	getSize(uint64_t size) {
	return (size >> 1);
}

uint64_t	packVariables(uint64_t size, bool allocated) {
	return (size << 1) | (allocated & 1);
}

uint64_t	setAllocated(uint64_t size, bool allocated) {
	return (size & ~1) | (allocated & 1);
}

uint64_t	setSize(uint64_t size, uint64_t value) {
	return (size & 1) | (value << 1);
}

void*	getTinyChunkData(t_tinychunk* chunk) {
	return ((void *)align((uint64_t)chunk + sizeof(t_tinychunk)));
}

void*	claimTinyChunk(t_zone* zone, t_tinychunk* chunk, size_t size) {
	chunk->size = packVariables(size, true);
	chunk->zone = zone;

	zone->reserved += align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);
	zone->used += size;
	zone->amount++;

	return (getTinyChunkData(chunk));
}

t_tinychunk*	findTinySpaceInZone(size_t size, t_zone* zone) {
	if (zone->reserved + align(sizeof(t_tinychunk) + size) > zone->size)
		return (NULL);

	t_tinychunk*	current_chunk = getFirstChunk(zone);
	t_tinychunk*	zone_limit = (void *)(current_chunk) + zone->size;
	uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

	while (current_chunk < zone_limit && isAllocated(current_chunk->size)) {
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

void*	getSmallChunkData(t_smallchunk* chunk) {
	return ((void *)align((uint64_t)chunk + sizeof(t_smallchunk)));
}

void	fragmentSmallChunk(t_zone* zone, t_smallchunk* chunk, uint64_t full_size) {
	if (!chunk->next)
		return ;

	t_smallchunk*	next_chunk = chunk->next;
	t_smallchunk*	new_chunk = (void *)((uint64_t)chunk + (uint64_t)full_size);

	if (isAllocated(next_chunk->size)) {
		if ((uint64_t)next_chunk - (uint64_t)new_chunk < align(sizeof(t_smallchunk)) + align(MALLOC_TINY_SIZE_LIMIT) + 1) {
			return ;
		}

		next_chunk->previous = new_chunk;
		new_chunk->next = next_chunk;
	}
	else {
		if (next_chunk->next)
			next_chunk->next->previous = new_chunk;
		else
			((t_smallchunk *)getFirstChunk(zone))->previous = new_chunk;

		new_chunk->next = next_chunk->next;
	}

	chunk->next = new_chunk;
	new_chunk->previous = chunk;
	new_chunk->size = packVariables(0, false);
	new_chunk->zone = zone;
}

void*	claimSmallChunk(t_zone* zone, t_smallchunk* chunk, size_t size) {
	chunk->size = packVariables(size, true);
	chunk->zone = zone;

	uint64_t full_chunk_size = align(sizeof(t_smallchunk)) + align(size);

	zone->reserved += full_chunk_size;
	zone->used += size;
	zone->amount++;

	fragmentSmallChunk(zone, chunk, full_chunk_size);

	return (getSmallChunkData(chunk));
}

t_smallchunk*	findSmallSpaceInZone(size_t size, t_zone* zone) {
	if (zone->reserved + align(sizeof(t_smallchunk) + size) > zone->size)
		return (NULL);

	t_smallchunk* current_chunk = getFirstChunk(zone);

	while (current_chunk) {
		if (!isAllocated(current_chunk->size)) {
			if (current_chunk->next) {
				if ((uint64_t)current_chunk->next - (uint64_t)getSmallChunkData(current_chunk) >= size) {
					return (current_chunk);
				}
			}
			else if ((uint64_t)(getFirstChunk(zone) + zone->size) - (uint64_t)getSmallChunkData(current_chunk) >= size){
				return (current_chunk);
			}
		}
		else if (!current_chunk->next && getSmallChunkData(current_chunk->previous) + align(getSize(current_chunk->previous->size)) < getFirstChunk(zone) + zone->size + align(sizeof(t_smallchunk)) + align(size)) {
			t_smallchunk* new_chunk = getSmallChunkData(current_chunk->previous) + align(getSize(current_chunk->previous->size));

			current_chunk->next = new_chunk;
			new_chunk->next = NULL;
			new_chunk->previous = current_chunk;
			new_chunk->size = packVariables(0, false);
			new_chunk->zone = zone;
		}

		current_chunk = current_chunk->next;
	}

	return (current_chunk);
}

t_smallchunk*	findSmallSpace(size_t size, t_zone** zone) {
	t_zone*		current_zone = malloc_singleton.small;

	while (current_zone) {
		t_smallchunk* found_chunk = findSmallSpaceInZone(size, current_zone);

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
	chunk->size = packVariables(size, true);
	chunk->zone = zone;

	zone->reserved = zone->size;
	zone->used = size;
	zone->amount++;

	return (getLargeChunkData(chunk));
}
