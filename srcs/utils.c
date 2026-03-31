#include "malloc.h"

void	printChunk(t_chunk* chunk) {
	ft_printf("---------- CHUNK ----------\n");
	if (chunk->status == ALLOCATED)
		ft_printf("Status: ALLOCATED\n");
	else
		ft_printf("Status: FREE\n");
	ft_printf("Size: %lu\nData pointer: %p\n\n", chunk->size, chunk->data);

	ft_printf("~~~~~~~~~~~ DATA ~~~~~~~~~~~\n\n");
	ft_print_memory(chunk->data, chunk->size);
}

void	printPage(t_page* page) {
	ft_printf("=========== PAGE ===========\nData pointer: %p\nAllocation amount: %lu\n\n",
		page->ptr,
		page->alloc_amount
	);

	t_chunk* current_chunk = page->chunks;
	while (current_chunk) {
		printChunk(current_chunk);
		ft_printf("\n");
		current_chunk = current_chunk->next;
	}
}

void	show_alloc_mem_ex() {
	t_allocator* allocator = (t_allocator *)malloc_singleton;
	if (!allocator)
		return ;

	ft_printf("\n<<<<<<<<<< MALLOC >>>>>>>>>>\n\n\n");
	t_page* current_page = allocator->pages;
	while (current_page) {
		printPage(current_page);
		ft_printf("\n");
		current_page = current_page->next;
	}
}
