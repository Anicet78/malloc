#include "malloc.h"

void*	newRawPage(size_t size) {
	//sysconf page max ...
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

t_page*	newInternalPage() {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;

	void* newPageInfos = newRawPage(MALLOC_REQUIRED_SIZE);
	if (!newPageInfos)
		return (NULL);

	allocator->page_ptr = newPageInfos;
	allocator->page_end = (t_page *)(newPageInfos + MALLOC_REQUIRED_SIZE);

	return newPageInfos;
}

t_page*	newPage(size_t size) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;
	t_page*			page_ptr = (t_page *)ft_smax((size_t)allocator->chunk_ptr, (size_t)allocator->page_ptr);

	if (page_ptr > (t_page *)((uint8_t *)allocator->page_end - sizeof(t_page))) {
		page_ptr = newInternalPage();
		if (!page_ptr)
			return (NULL);
	}

	void* raw_page = newRawPage(size);
	if (!raw_page)
		return (NULL);

	page_ptr->chunks = (t_chunk *)((uint8_t *)page_ptr + sizeof(t_page));
	allocator->chunk_ptr = (t_chunk *)((uint8_t *)page_ptr->chunks + sizeof(t_chunk));
	page_ptr->ptr = raw_page;
	page_ptr->alloc_amount = 0;
	page_ptr->next = NULL;
	if (allocator->pages) {
		allocator->pages->previous->next = page_ptr;
		page_ptr->previous = allocator->pages->previous;
	}
	else
		allocator->pages = page_ptr;
	allocator->pages->previous = page_ptr;

	t_chunk* chunk = page_ptr->chunks;
	chunk->status = FREE;
	chunk->data = raw_page;
	chunk->size = size;
	chunk->next = NULL;
	chunk->previous = chunk;

	return page_ptr;
}

t_chunk*	findSpace(t_page* page, size_t size) {
	t_chunk*	current_chunk = page->chunks;

	while (current_chunk) {
		if (current_chunk->status == FREE && current_chunk->size >= size)
			return current_chunk;
		current_chunk = current_chunk->next;
	}
	return (NULL);
}

void*	newChunk(t_page* page, size_t size, t_chunk* free_chunk) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;

	if (free_chunk->size > size) {
		t_chunk* rem_chunk = (t_chunk *)ft_smax((size_t)allocator->chunk_ptr, (size_t)allocator->page_ptr);

		if ((t_page *)rem_chunk > (t_page *)((uint8_t *)allocator->page_end - sizeof(t_chunk))) {
			void* newPageInfos = newInternalPage();
			if (!newPageInfos)
				return (NULL);
			rem_chunk = (t_chunk *)((uint8_t *)newPageInfos + sizeof(t_page));
		}

		allocator->chunk_ptr = (t_chunk *)((uint8_t *)rem_chunk + sizeof(t_chunk));

		rem_chunk->status = FREE;
		rem_chunk->data = (uint8_t *)free_chunk->data + size;
		rem_chunk->size = free_chunk->size - size;
		rem_chunk->next = free_chunk->next;
		rem_chunk->previous = free_chunk;

		if (free_chunk->next)
			free_chunk->next->previous = rem_chunk;
		else
			page->chunks->previous = rem_chunk;

		free_chunk->next = rem_chunk;
	}

	free_chunk->status = ALLOCATED;
	free_chunk->size = size;
	page->alloc_amount++;

	return free_chunk->data;
}
