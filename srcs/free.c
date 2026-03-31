#include "malloc.h"

void	deleteChunk(t_chunk* chunk) {
	chunk->status = UNKNOWN;
	chunk->data = NULL;
	chunk->size = 0;
}

void	deletePage(t_page* page) {
	munmap(page->ptr, page->chunks->size);
	page->ptr = NULL;
}

void	unAllocate(t_chunk* chunk, t_page* page) {
	t_chunk*	next = chunk->next;
	t_chunk*	previous = chunk->previous;

	chunk->status = FREE;
	page->alloc_amount--;

	if (next && next->status == FREE && chunk->size + next->size >= chunk->size) {
		chunk->size += next->size;
		deleteChunk(next);
	}

	if (previous && previous->next != NULL && previous->status == FREE && chunk->size + previous->size >= chunk->size) {
		previous->size += chunk->size;
		deleteChunk(chunk);
	}

	if (page->alloc_amount == 0) {
		deleteChunk(page->chunks);
		deletePage(page);
		return ;
	}
}

void	free(void *ptr) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;
	t_page*			current_page = allocator->pages;

	while (current_page) {
		t_chunk* current_chunk = current_page->chunks;

		while (current_page->ptr > NULL && current_chunk) {
			if (current_chunk->data == ptr) {
				unAllocate(current_chunk, current_page);
				return ;
			}
			current_chunk = current_chunk->next;
		}
		current_page = current_page->next;
	}
}