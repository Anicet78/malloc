#include "malloc.h"

inline void*	getFirstChunk(t_zone* zone) {
	return ((void *)align((uint64_t)zone + sizeof(t_zone)));
}

inline void*	getZoneEnd(t_zone* zone) {
	return (getFirstChunk(zone) + zone->size);
}

t_zone*	lowerBound(t_zone* zone_ptr, t_zone* zone_list) {
	while (zone_list->next && zone_list->next < zone_ptr) {
		zone_list = zone_list->next;
	}

	return (zone_list);
}

void	insertZone(t_zone* zone_ptr, t_zone** zone_list) {
	if (*zone_list == NULL) {
		*zone_list = zone_ptr;
		zone_ptr->previous = zone_ptr;
		zone_ptr->next = NULL;
	}
	else if (zone_ptr < *zone_list) {
		zone_ptr->next = *zone_list;
		zone_ptr->previous = (*zone_list)->previous;
		(*zone_list)->previous = zone_ptr;
		*zone_list = zone_ptr;
	}
	else {
		t_zone* zoneEmplacement = lowerBound(zone_ptr, *zone_list);
		zone_ptr->next = zoneEmplacement->next;
		zone_ptr->previous = zoneEmplacement;
		if (zoneEmplacement->next)
			zoneEmplacement->next->previous = zone_ptr;
		else
			(*zone_list)->previous = zone_ptr;
		zoneEmplacement->next = zone_ptr;
	}
}

t_zone*	tinyZone(uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + MALLOC_TINY_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.tiny);

	t_tinychunk*	chunk = getFirstChunk(zone_ptr);
	t_tinychunk*	zone_limit = (t_tinychunk *)((uint64_t)zone_ptr + (*zone_size));
	uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);
	*zone_size -= (uint64_t)chunk - (uint64_t)zone_ptr;

	while (chunk < zone_limit) {
		chunk->size = packVariables(0, false);
		chunk = (t_tinychunk *)((uint64_t)chunk + chunk_size);
	}

	return (zone_ptr);
}

t_zone*	smallZone(uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + MALLOC_SMALL_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.small);

	t_smallchunk* chunk = getFirstChunk(zone_ptr);
	chunk->next = NULL;
	chunk->previous = chunk;
	chunk->size = packVariables(0, false);
	chunk->zone = zone_ptr;

	*zone_size -= (uint64_t)chunk - (uint64_t)zone_ptr;

	return (zone_ptr);
}

t_zone*	largeZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_largechunk) + size));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	insertZone(zone_ptr, &malloc_singleton.large);

	t_largechunk* chunk = getFirstChunk(zone_ptr);
	chunk->size = setSize(chunk->size, size);
	chunk->zone = zone_ptr;

	*zone_size -= (uint64_t)chunk - (uint64_t)zone_ptr;

	return (zone_ptr);
}

t_zone*	newZone(size_t size) {
	t_zone*		zone_ptr;
	uint64_t	zone_size;

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		zone_ptr = tinyZone(&zone_size);
	else if (size <= MALLOC_SMALL_SIZE_LIMIT)
		zone_ptr = smallZone(&zone_size);
	else
		zone_ptr = largeZone(size, &zone_size);

	if (zone_ptr == NULL)
		return (NULL);

	zone_ptr->size = zone_size;
	zone_ptr->reserved = 0;
	zone_ptr->used = 0;
	zone_ptr->amount = 0;

	return (zone_ptr);
}
