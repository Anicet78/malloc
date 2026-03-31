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

void*	allocate(t_allocator* allocator, size_t size) {
	t_page*	current_page = allocator->pages;
	t_chunk* space = NULL;

	while (current_page) {
		space = findSpace(current_page, size);
		if (space != NULL)
			return (newChunk(current_page, size, space));
		current_page = current_page->next;
	}

	t_page*	newPagePtr = newPage(size);
	if (!newPagePtr)
		return (NULL);

	space = findSpace(newPagePtr, size);
	if (!space)
		return (NULL);

	return (newChunk(newPagePtr, size, space));
}

void*	malloc(size_t size) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;
	if (!allocator) {
		allocator = firstAlloc();
		malloc_singleton = allocator;
	}

	if (!allocator)
		return (NULL);

	return (allocate(allocator, size));
}
