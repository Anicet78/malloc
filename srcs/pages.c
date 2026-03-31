#include "malloc.h"

size_t	calcPageSize(size_t size) {
	size_t pagesize = sysconf(_SC_PAGESIZE);
	size_t finalSize;

	if (size == 0)
		return (pagesize);
	finalSize = (size / pagesize + (size % pagesize != 0)) * pagesize;
	if (finalSize < size)
		return (0);
	return (finalSize);
}

void*	newRawPage(size_t size) {
	void* ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
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

	size = calcPageSize(size);
	if (!size)
		return (NULL);

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
	if (page->ptr == NULL) return NULL;

	t_chunk* current_chunk = page->chunks;

	while (current_chunk) {
		if (current_chunk->status == FREE && current_chunk->size >= size)
			return current_chunk;
		current_chunk = current_chunk->next;
	}
	return (NULL);
}

void*	subdivide(t_page* page, size_t size, t_chunk* free_chunk) {
	t_allocator*	allocator = (t_allocator *)malloc_singleton;
	t_chunk*		new_chunk = (t_chunk *)ft_smax((size_t)allocator->chunk_ptr, (size_t)allocator->page_ptr);

	if ((t_page *)new_chunk > (t_page *)((uint8_t *)allocator->page_end - sizeof(t_chunk))) {
		void* newPageInfos = newInternalPage();
		if (!newPageInfos)
			return (NULL);
		new_chunk = (t_chunk *)((uint8_t *)newPageInfos + sizeof(t_page));
	}

	allocator->chunk_ptr = (t_chunk *)((uint8_t *)new_chunk + sizeof(t_chunk));

	new_chunk->status = FREE;
	new_chunk->data = (uint8_t *)free_chunk->data + size;
	new_chunk->size = free_chunk->size - size;
	new_chunk->next = free_chunk->next;
	new_chunk->previous = free_chunk;

	if (free_chunk->next)
		free_chunk->next->previous = new_chunk;
	else
		page->chunks->previous = new_chunk;

	free_chunk->next = new_chunk;

	return (free_chunk);
}

void*	newChunk(t_page* page, size_t size, t_chunk* free_chunk) {
	if (free_chunk->size > size) {
		if (!subdivide(page, size, free_chunk))
			return (NULL);
	}

	free_chunk->status = ALLOCATED;
	free_chunk->size = size;
	page->alloc_amount++;

	return free_chunk->data;
}
