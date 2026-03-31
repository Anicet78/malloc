#include "malloc.h"

void	printChunk(t_chunk* chunk) {
	ft_printf("\033[1;34m----------- CHUNK ----------\033[0m\n");
	if (chunk->status == ALLOCATED)
		ft_printf("Status: \033[1;31mALLOCATED\033[0m\n");
	else
		ft_printf("Status: \033[1;32mFREE\033[0m\n");
	ft_printf("Size: %lu\nData pointer: %p\n\n", chunk->size, chunk->data);

	if (chunk->status == ALLOCATED) {
		ft_printf("\033[36m~~~~~~~~~~~ DATA ~~~~~~~~~~~\033[0m\n");
		ft_print_memory(chunk->data, chunk->size);
		ft_printf("\n");
	}
}

void	printPage(t_page* page) {
	ft_printf("\033[1;33m=========== PAGE ===========\033[0m\nData pointer: %p\nAllocation amount: %lu\n\n",
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

	ft_printf("\n\033[1;35m<<<<<<<<<< MALLOC >>>>>>>>>>\033[0m\n\n\n");
	t_page* current_page = allocator->pages;
	while (current_page) {
		printPage(current_page);
		ft_printf("\n");
		current_page = current_page->next;
	}
}
