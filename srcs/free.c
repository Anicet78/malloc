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

	munmap(zone, zone->size + align(sizeof(t_zone)));
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
	zone->amount--;
	zone->used -= align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

	chunk->size = 0;
	chunk->allocated = false;
}

void	MyFree(void* ptr) {
	uint64_t size = *(uint64_t *)(ptr - ALIGNMENT);

	if (size <= MALLOC_TINY_SIZE_LIMIT)
		freeTiny(ptr - align(sizeof(t_tinychunk)));
	// else if (size <= MALLOC_SMALL_SIZE_LIMIT)
	// 	smallAlloc(size);
	// else
	// 	largeAlloc(size);
}
