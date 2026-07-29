#include "malloc.h"

t_allocator malloc_singleton;

void*	tinyAlloc(size_t size)
{
	t_zone*			zone;
	t_tinychunk*	chunk = findTinySpace(size, &zone);

	if (chunk)
		return ((void *)align((uint64_t)chunk + sizeof(t_tinychunk)));

	zone = newZone(size);
	if (!zone)
		return (NULL);

	chunk = findTinySpaceInZone(size, zone);
	if (!chunk)
		return (NULL);

	zone->amount++;
	zone->used += align(sizeof(t_tinychunk) + MALLOC_SMALL_SIZE_LIMIT);

	return ((void *)align((uint64_t)chunk + sizeof(t_tinychunk)));
}

void*	malloc(size_t size) {
	if (size <= MALLOC_TINY_SIZE_LIMIT)
		return (tinyAlloc(size));
	return (NULL);
	// else if (size <= MALLOC_SMALL_SIZE_LIMIT)
	// 	return (smallAlloc(size));
	// return (largeAlloc(size));
}
