#include "malloc.h"

static void	printTiny(uint64_t* total_bytes) {
	if (!malloc_singleton.tiny)
		return ;

	t_zone*		first_zone = malloc_singleton.tiny->previous;
	t_zone*		current_zone = first_zone;
	uint64_t	zone_index = 1;

	ft_printf("TINY : %p\n", current_zone);

	while (current_zone != first_zone || zone_index == 1) {
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

		zone_index++;
		current_zone = current_zone->previous;
	}
}

static void	printSmall(uint64_t* total_bytes) {
	if (!malloc_singleton.small)
		return ;

	t_zone*		first_zone = malloc_singleton.small->previous;
	t_zone*		current_zone = first_zone;
	uint64_t	zone_index = 1;

	ft_printf("SMALL : %p\n", current_zone);

	while (current_zone != first_zone || zone_index == 1) {
		t_smallchunk*	current_chunk = getFirstChunk(current_zone);

		(*total_bytes) += current_zone->used;

		while (current_chunk) {
			if (current_chunk->allocated == true) {
				ft_printf("%p — %p : %lu byte%s\n", (uint64_t)getSmallChunkData(current_chunk), (uint64_t)getSmallChunkData(current_chunk) + current_chunk->size, current_chunk->size, current_chunk->size == 1 ? "" : "s");
			}
			current_chunk = current_chunk->next;
		}

		zone_index++;
		current_zone = current_zone->previous;
	}
}

void	printLarge(uint64_t* total_bytes) {
	if (!malloc_singleton.large)
		return ;

	t_zone*		first_zone = malloc_singleton.large->previous;
	t_zone*		current_zone = first_zone;
	uint64_t	zone_index = 1;

	ft_printf("LARGE : %p\n", first_zone);

	while (current_zone != first_zone || zone_index == 1) {
		t_largechunk* current_chunk = getFirstChunk(current_zone);

		(*total_bytes) += current_zone->used;

		if (current_chunk->allocated == true) {
			ft_printf("%p — %p : %lu byte%s\n", (uint64_t)getLargeChunkData(current_chunk), (uint64_t)getLargeChunkData(current_chunk) + current_chunk->size, current_chunk->size, current_chunk->size == 1 ? "" : "s");
		}

		zone_index++;
		current_zone = current_zone->previous;
	}
}

void	show_alloc_mem() {
	ft_printf("\n%s<<<<<<<<<< MALLOC >>>>>>>>>>%s\n\n", COLOR_LIGHT_PURPLE, COLOR_NC);

	uint64_t total_bytes = 0;

	printTiny(&total_bytes);
	printSmall(&total_bytes);
	printLarge(&total_bytes);

	ft_printf("Total : %lu byte%s\n", total_bytes, total_bytes <= 1 ? "" : "s");
}