#include "malloc.h"

static void	printTiny(uint64_t* total_bytes) {
	t_zone*		current_zone = malloc_singleton.tiny;

	if (!current_zone)
		return ;

	ft_printf("TINY : %p\n", current_zone);

	while (current_zone) {
		t_tinychunk*	current_chunk = getFirstChunk(current_zone);
		t_tinychunk*	zone_limit = (void *)(current_chunk) + current_zone->size;
		uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

		(*total_bytes) += current_zone->used;

		while (current_chunk < zone_limit) {
			if (current_chunk->allocated == true) {
				ft_printf("%p — %p : %lu byte%s\n", (uint64_t)getTinyChunkData(current_chunk), (uint64_t)getTinyChunkData(current_chunk) + current_chunk->size, current_chunk->size, current_chunk->size == 1 ? "" : "s");
			}
			current_chunk = (t_tinychunk *)((uint64_t)current_chunk + chunk_size);
		}
		current_zone = current_zone->next;
	}
}

void	printLarge(uint64_t* total_bytes) {
	t_zone*		current_zone = malloc_singleton.large;

	if (!current_zone)
		return ;

	ft_printf("LARGE : %p\n", current_zone);

	while (current_zone) {
		t_largechunk* current_chunk = getFirstChunk(current_zone);

		(*total_bytes) += current_zone->used;

		if (current_chunk->allocated == true) {
			ft_printf("%p — %p : %lu byte%s\n", (uint64_t)getLargeChunkData(current_chunk), (uint64_t)getLargeChunkData(current_chunk) + current_chunk->size, current_chunk->size, current_chunk->size == 1 ? "" : "s");
		}

		current_zone = current_zone->next;
	}
}

void	show_alloc_mem() {
	ft_printf("\n%s<<<<<<<<<< MALLOC >>>>>>>>>>%s\n\n", COLOR_LIGHT_PURPLE, COLOR_NC);

	uint64_t total_bytes = 0;

	printTiny(&total_bytes);
	printLarge(&total_bytes);

	ft_printf("Total : %lu byte%s\n", total_bytes, total_bytes <= 1 ? "" : "s");
}