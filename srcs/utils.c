#include "malloc.h"

void	printChunk(t_chunk* chunk) {
	ft_printf("========== CHUNK: %p ==========\n\tnext: %p\n\tcapacity: %lu\n\tcount: %lu\n\tdata: %p\n\n",
		chunk,
		chunk->next,
		chunk->capacity,
		chunk->count,
		chunk->data
	);

	ft_printf("---------- DATA ----------\n");
	ft_print_memory(chunk->data, chunk->capacity);
}

void	show_alloc_mem_ex() {
	t_allocator* allocator = (t_allocator *)malloc_singleton;
	if (!allocator)
		return ;

	ft_printf("<<<<<<<<<< ALLOCATOR >>>>>>>>>>\n\n");
	t_chunk* current_chunk = allocator->begin;
	while (current_chunk) {
		printChunk(current_chunk);
		ft_printf("\n");
		current_chunk = current_chunk->next;
	}
}
