#include "malloc.h"

t_zone*	searchZone(void* ptr, t_zone* zone) {
	if (!zone)
		return (NULL);

	while (ptr > (void *)zone && zone->next)
		zone = zone->next;

	return (zone);
}

void	deleteZone(t_zone* zone) {
	zone->previous->next = zone->next;
	if (zone->next)
		zone->next->previous = zone->previous;

	munmap(zone, align(sizeof(t_zone) + zone->size));
}

void	freeTiny(t_tinychunk* chunk) {
	t_zone* zone = searchZone(chunk, malloc_singleton.tiny);
	if (zone == NULL)
		return ;

	if (zone->amount <= 1) {
		if (malloc_singleton.tiny == zone)
			malloc_singleton.tiny = NULL;
		deleteZone(zone);
		return ;
	}
	zone->reserved -= align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);
	zone->used -= align(sizeof(t_tinychunk) + chunk->size);
	zone->amount--;

	chunk->size = 0;
	chunk->allocated = false;
}

void	freeLarge(t_largechunk* chunk) {
	t_zone* zone = searchZone(chunk, malloc_singleton.large);
	if (zone == NULL)
		return ;

	if (malloc_singleton.large == zone)
		malloc_singleton.large = NULL;
	deleteZone(zone);
}

void	MyFree(void* ptr) {
	uint64_t size = *(uint64_t *)(ptr - ALIGNMENT);

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		freeTiny(ptr - align(sizeof(t_tinychunk)));
	// else if (size <= MALLOC_SMALL_SIZE_LIMIT)
	// 	smallAlloc(size);
	else
		freeLarge(ptr - align(sizeof(t_largechunk)));
}
