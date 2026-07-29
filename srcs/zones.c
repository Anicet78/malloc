#include "malloc.h"

t_zone*	lowerBound(t_zone* zone_ptr, t_zone* zone_list) {
	while (zone_list->next && zone_list < zone_ptr) {
		zone_list = zone_list->next;
	}

	if (zone_list->next)
		return zone_list->previous;

	return (zone_list);
}

void	insertZone(t_zone* zone_ptr, t_zone** zone_list) {
	if (*zone_list == NULL)
		*zone_list = zone_ptr;
	else {
		t_zone* zoneEmplacement = lowerBound(zone_ptr, *zone_list);
		zone_ptr->next = zoneEmplacement->next;
		zone_ptr->previous = zoneEmplacement;
		zoneEmplacement->next->previous = zone_ptr;
		zoneEmplacement->next = zone_ptr;
	}
}

t_zone*	tinyZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_tinychunk) + MALLOC_TINY_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.tiny);

	t_tinychunk*	chunk = getFirstChunk(zone_ptr);
	t_tinychunk*	zone_limit = (uint64_t *)(chunk) + (*zone_size);
	uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_SMALL_SIZE_LIMIT);

	while (chunk < zone_limit) {
		chunk->allocated = false;
		chunk->size = 0;
		chunk += chunk_size;
	}

	return (zone_ptr);
}

t_zone*	smallZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_smallchunk) + MALLOC_SMALL_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.small);

	t_smallchunk* chunk = getFirstChunk(zone_ptr);
	chunk->allocated = false;
	chunk->size = MALLOC_SMALL_ZONE_SIZE;
	chunk->next = NULL;
	chunk->previous = chunk;
}

t_zone*	largeZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_largechunk) + size));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.large);

	t_largechunk* chunk = getFirstChunk(zone_ptr);
	chunk->allocated = false;
	chunk->size = 0;
}

t_zone*	newZone(size_t size) {
	t_zone*		zone_ptr;
	uint64_t	zone_size;

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		zone_ptr = tinyZone(size, &zone_size);
	else if (size <= MALLOC_SMALL_SIZE_LIMIT)
		zone_ptr = smallZone(size, &zone_size);
	else
		zone_ptr = largeZone(size, &zone_size);

	if (zone_ptr == NULL)
		return (NULL);

	zone_ptr->size = zone_size;
	zone_ptr->used = 0;
	zone_ptr->amount = 0;
}
