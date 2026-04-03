#include "malloc.h"

volatile t_allocator* malloc_singleton;

t_allocator*	firstAlloc() {
	t_allocator* allocator = newRawPage(MALLOC_REQUIRED_SIZE);
	if (!allocator)
		return (NULL);

	allocator->pages = NULL;
	allocator->page_ptr = (t_page *)((uint8_t *)allocator + sizeof(t_allocator));
	allocator->chunk_ptr = NULL;
	allocator->page_end = (t_page *)((uint8_t *)allocator + MALLOC_REQUIRED_SIZE);

	return (allocator);
}

void*	allocate(size_t size) {
	t_page*		page = NULL;
	t_chunk*	empty_chunk1 = NULL;
	t_chunk*	empty_chunk2 = NULL;

	t_chunk* space = findSpace(size, &page, &empty_chunk1, &empty_chunk2);
	if (space)
		return (newChunk(page, size, space, empty_chunk1));

	t_page* newPagePtr = newPage(size, page);
	if (!newPagePtr)
		return (NULL);

	return (newChunk(newPagePtr, size, newPagePtr->chunks, newPagePtr->chunks == empty_chunk1 ? empty_chunk2 : empty_chunk1));
}

void*	malloc(size_t size) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;
	if (!allocator) {
		allocator = firstAlloc();
		malloc_singleton = allocator;
	}

	if (!allocator)
		return (NULL);

	return (allocate(size));
}
