#include "malloc.h"

void	printTiny(uint64_t* total_allocations) {
	t_zone*		current_zone = malloc_singleton.tiny;
	uint64_t	zone_index = 1;

	if (!current_zone)
		return ;

	ft_printf("%s=========== TINY ===========%s\n\n", COLOR_YELLOW, COLOR_NC);

	while (current_zone) {
		ft_printf("%s---------- Zone %d ----------%s\n\n", COLOR_LIGHT_GRAY, zone_index, COLOR_NC);

		t_tinychunk*	current_chunk = getFirstChunk(current_zone);
		t_tinychunk*	zone_limit = (void *)(current_chunk) + current_zone->size;
		uint64_t		chunk_size = align(sizeof(t_tinychunk) + MALLOC_TINY_SIZE_LIMIT);

		while (current_chunk < zone_limit && current_chunk->allocated == true) {
			ft_printf("%s########## CHUNK ###########%s\n", COLOR_LIGHT_BLUE);
			if (current_chunk->allocated == true) {
				ft_printf("Status: %sALLOCATED%s\n",COLOR_LIGHT_RED, COLOR_NC);
				(*total_allocations)++;
			}
			else
				ft_printf("Status: %sFREE%s\n", COLOR_LIGHT_GREEN, COLOR_NC);
			ft_printf("Size: %lu\n", current_chunk->size);

			if (current_chunk->allocated == true) {
				ft_printf("\n%s~~~~~~~~~~~ DATA ~~~~~~~~~~~%s\n", COLOR_LIGHT_CYAN, COLOR_NC);
				ft_print_memory((void *)align((uint64_t)current_chunk + sizeof(t_tinychunk)), current_chunk->size);
				ft_printf("\n");
			}
			current_chunk += chunk_size;
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

	ft_printf("%lu allocation%s found\n", total_allocations, total_allocations == 1 ? "" : "s");

}
