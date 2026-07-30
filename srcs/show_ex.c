#include "malloc.h"

static void	printTiny(uint64_t* total_allocations) {
	t_zone*		current_zone = malloc_singleton.tiny;
	uint64_t	zone_index = 1;

	if (!current_zone)
		return ;

	ft_printf("%s=========== TINY ===========%s\n\n", COLOR_YELLOW, COLOR_NC);

	while (current_zone) {
		ft_printf("%s---------- Zone %d ----------%s\nSize: %lu\nReserved: %lu\nUsed: %lu\nAllocation amount: %lu\n\n", COLOR_LIGHT_GRAY, zone_index, COLOR_NC, current_zone->size, current_zone->reserved, current_zone->used, current_zone->amount);

		t_tinychunk*	current_chunk = getFirstChunk(current_zone);
		t_tinychunk*	zone_limit = (void *)(current_chunk) + current_zone->size;
		uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

		while (current_chunk < zone_limit) {
			ft_printf("%s########## CHUNK ###########%s\n", COLOR_LIGHT_BLUE, COLOR_NC);

			if (current_chunk->allocated == true) {
				ft_printf("Status: %sALLOCATED%s\n",COLOR_LIGHT_RED, COLOR_NC);
				(*total_allocations)++;
				ft_printf("Size: %lu\n", current_chunk->size);
				ft_printf("%s~~~~~~~~~~~ DATA ~~~~~~~~~~~%s\n", COLOR_LIGHT_GRAY, COLOR_NC);
				ft_print_memory((void *)align((uint64_t)current_chunk + sizeof(t_tinychunk)), current_chunk->size);
				ft_printf("\n");
			}
			else {
				ft_printf("Status: %sFREE%s\n\n", COLOR_LIGHT_GREEN, COLOR_NC);
			}
			current_chunk = (t_tinychunk *)((uint64_t)current_chunk + chunk_size);
		}
		current_zone = current_zone->next;
		zone_index++;
	}
}

void	show_alloc_mem_ex() {
	ft_printf("\n%s<<<<<<<<<< MALLOC >>>>>>>>>>%s\n\n\n", COLOR_LIGHT_PURPLE, COLOR_NC);

	uint64_t total_allocations = 0;

	printTiny(&total_allocations);

	if (total_allocations == 0) {
		ft_printf("--> NO HEAP ALLOCATIONS FOUND <--\n\n");
		return ;
	}

	ft_printf("%lu allocation%s\n", total_allocations, total_allocations == 1 ? "" : "s");
}
