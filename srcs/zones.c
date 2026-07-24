#include "malloc.h"

t_zone*	lowerBound(t_zone* zone_ptr, t_zone* zone_list) {
	while (zone_list->next && zone_list < zone_ptr) {
		zone_list = zone_list->next;
	}
	if (zone_list->next)
		return zone_list->previous;
	return zone_list;
}

t_zone*	tinyZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_tinychunk) + MALLOC_TINY_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	if (malloc_singleton.tiny == NULL)
		malloc_singleton.tiny = zone_ptr;
	else {
		t_zone* zoneEmplacement = lowerBound(zone_ptr, malloc_singleton.tiny);
		zone_ptr->next = zoneEmplacement->next;
		zone_ptr->previous = zoneEmplacement;
		zoneEmplacement->next->previous = zone_ptr;
		zoneEmplacement->next = zone_ptr;
	}

	t_tinychunk* chunk = getFirstChunk(zone_ptr);
	chunk->allocated = false;
	chunk->size = *zone_size;
}

t_zone*	smallZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_smallchunk) + MALLOC_SMALL_ZONE_SIZE));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	if (malloc_singleton.small == NULL)
		malloc_singleton.small = zone_ptr;
	else {
		t_zone* zoneEmplacement = lowerBound(zone_ptr, malloc_singleton.small);
		zone_ptr->next = zoneEmplacement->next;
		zone_ptr->previous = zoneEmplacement;
		zoneEmplacement->next->previous = zone_ptr;
		zoneEmplacement->next = zone_ptr;
	}

	t_smallchunk* chunk = getFirstChunk(zone_ptr);
	chunk->allocated = false;
	chunk->size = *zone_size;
	chunk->next = NULL;
	chunk->previous = chunk;
}

t_zone*	largeZone(size_t size, uint64_t* zone_size) {
	*zone_size = calcPageSize(align(sizeof(t_zone) + sizeof(t_largechunk) + size));

	t_zone*	zone_ptr = newRawPage(*zone_size);
	if (!zone_ptr)
		return (NULL);

	if (malloc_singleton.large == NULL)
		malloc_singleton.large = zone_ptr;
	else {
		t_zone* zoneEmplacement = lowerBound(zone_ptr, malloc_singleton.large);
		zone_ptr->next = zoneEmplacement->next;
		zone_ptr->previous = zoneEmplacement;
		zoneEmplacement->next->previous = zone_ptr;
		zoneEmplacement->next = zone_ptr;
	}

	t_largechunk* chunk = getFirstChunk(zone_ptr);
	chunk->allocated = false;
	chunk->size = *zone_size;
}

t_zone*	newZone(size_t size) {
	t_zone*		zone_ptr;
	uint64_t*	zone_size;

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		zone_ptr = tinyZone(size, &zone_size);
	else if (size <= MALLOC_SMALL_SIZE_LIMIT)
		zone_ptr = smallZone(size, &zone_size);
	else
		zone_ptr = largeZone(size, &zone_size);

	if (zone_ptr == NULL)
		return NULL;

	zone_ptr->next = NULL;
	zone_ptr->previous = zone_ptr;
	zone_ptr->size = zone_size;
	zone_ptr->used = 0;
	zone_ptr->amount = 0;
}

t_tinychunk*	findTinySpace(size_t size, t_zone** zone) {
	t_zone* current_zone = malloc_singleton.tiny;

	while (current_zone) {
		if (current_zone->used + align(sizeof(t_tinychunk) + size) > current_zone->size) {
			t_tinychunk* current_chunk = getFirstChunk(current_zone);
			while (current_chunk < getFirstChunk(current_zone) + current_zone->size && (current_chunk->allocated == true || current_chunk->size < size)) {
				current_chunk += align(sizeof(t_tinychunk) + MALLOC_SMALL_SIZE_LIMIT);
			}
			if (current_chunk < getFirstChunk(current_zone) + current_zone->size)
				return (current_chunk);
		}
		current_zone = current_zone->next;
	}

	if (!current_zone)
		return (NULL);


	return ;
}
