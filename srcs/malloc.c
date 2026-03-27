#include "malloc.h"

volatile t_allocator* malloc_singleton;

void*	newBlock(size_t size) {
	// sysconf(_SC_PAGESIZE)
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

void	*newChunk(size_t size) {
	t_chunk* chunk = newBlock(size);

	if (!chunk)
		return (NULL);
	chunk->data = (uint8_t*)(chunk + sizeof(t_chunk));
	chunk->capacity = size - sizeof(t_chunk);
	chunk->count = 0;
	chunk->next = NULL;

	return (chunk);
}

t_allocator*	firstAlloc() {
	t_allocator* allocator = newBlock(MALLOC_REQUIRED_SIZE);

	if (!allocator)
		return (NULL);
	allocator->begin = (t_chunk*)(allocator + sizeof(t_allocator));
	allocator->begin->data = (uint8_t*)(allocator->begin + sizeof(t_chunk));
	allocator->begin->capacity = MALLOC_REQUIRED_SIZE - (sizeof(t_allocator) + sizeof(t_chunk));
	allocator->begin->count = 0;
	allocator->begin->next = NULL;

	return (allocator);
}

void*	allocate(t_allocator* allocator, size_t size) {
	t_chunk*	current_chunk = allocator->begin;

	while (current_chunk) {
		if (allocator->begin->capacity - allocator->begin->count > size)
			break ;
		if (current_chunk->next == NULL) {
			current_chunk->next = newChunk(size);
			current_chunk = current_chunk->next;
			break ;
		}
		current_chunk = current_chunk->next;
	}
	if (!current_chunk)
		return (NULL);

	current_chunk->count += size;

	return (current_chunk->data + current_chunk->count - size);
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
