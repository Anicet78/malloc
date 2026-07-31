#include "malloc.h"

t_allocator malloc_singleton;

void*	tinyAlloc(size_t size)
{
	t_zone*			zone;
	t_tinychunk*	chunk = findTinySpace(size, &zone);

	if (chunk)
		return (claimTinyChunk(zone, chunk, size));

	zone = newZone(size);
	if (!zone)
		return (NULL);

	chunk = findTinySpaceInZone(size, zone);
	if (!chunk)
		return (NULL);

	return (claimTinyChunk(zone, chunk, size));
}

void*	smallAlloc(size_t size) {
	t_zone*			zone;
	t_smallchunk*	chunk = findSmallSpace(size, &zone);

	if (chunk)
		return (claimSmallChunk(zone, chunk, size));

	zone = newZone(size);
	if (!zone)
		return (NULL);

	chunk = findSmallSpaceInZone(size, zone);
	if (!chunk)
		return (NULL);

	return (claimSmallChunk(zone, chunk, size));
}

void*	largeAlloc(size_t size) {
	t_zone* zone = newZone(size);
	if (!zone)
		return (NULL);

	t_largechunk* chunk = getFirstChunk(zone);

	return (claimLargeChunk(zone, chunk, size));
}

void*	MyMalloc(size_t size) {
	if (size <= MALLOC_TINY_SIZE_LIMIT)
		return (tinyAlloc(size));
	else if (size <= MALLOC_SMALL_SIZE_LIMIT)
		return (smallAlloc(size));
	return (largeAlloc(size));
}
