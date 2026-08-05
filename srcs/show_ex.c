#include "malloc.h"

static void	printTiny(uint64_t* total_allocations, uint64_t* total_bytes) {
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

		(*total_bytes) += current_zone->used;
		(*total_allocations) += current_zone->amount;

		while (current_chunk < zone_limit) {

			if (isAllocated(current_chunk->size)) {
				ft_printf("%s########## CHUNK ###########%s\n", COLOR_LIGHT_BLUE, COLOR_NC);
				ft_printf("Status: %sALLOCATED%s\n",COLOR_LIGHT_RED, COLOR_NC);
				ft_printf("Size: %lu\n", getSize(current_chunk->size));
				ft_printf("%s~~~~~~~~~~~ DATA ~~~~~~~~~~~%s\n", COLOR_LIGHT_GRAY, COLOR_NC);
				ft_print_memory((void *)align((uint64_t)current_chunk + sizeof(t_tinychunk)), getSize(current_chunk->size));
				ft_printf("\n");
			}
			current_chunk = (t_tinychunk *)((uint64_t)current_chunk + chunk_size);
		}

		zone_index++;
		current_zone = current_zone->next;
	}
}

static void	printSmall(uint64_t* total_allocations, uint64_t* total_bytes) {
	if (!malloc_singleton.small)
		return ;

	t_zone*		first_zone = malloc_singleton.small->previous;
	t_zone*		current_zone = first_zone;
	uint64_t	zone_index = 1;

	ft_printf("%s=========== SMALL ===========%s\n\n", COLOR_YELLOW, COLOR_NC);

	while (current_zone != first_zone || zone_index == 1) {
		ft_printf("%s---------- Zone %d ----------%s\nSize: %lu\nReserved: %lu\nUsed: %lu\nAllocation amount: %lu\n\n", COLOR_LIGHT_GRAY, zone_index, COLOR_NC, current_zone->size, current_zone->reserved, current_zone->used, current_zone->amount);

		t_smallchunk*	current_chunk = getFirstChunk(current_zone);

		(*total_bytes) += current_zone->used;
		(*total_allocations) += current_zone->amount;

		while (current_chunk) {
			ft_printf("%s########## CHUNK ###########%s\n", COLOR_LIGHT_BLUE, COLOR_NC);

			if (isAllocated(current_chunk->size)) {
				ft_printf("Status: %sALLOCATED%s\n",COLOR_LIGHT_RED, COLOR_NC);
				ft_printf("Size: %lu\n", getSize(current_chunk->size));
				ft_printf("%s~~~~~~~~~~~ DATA ~~~~~~~~~~~%s\n", COLOR_LIGHT_GRAY, COLOR_NC);
				ft_print_memory((void *)align((uint64_t)current_chunk + sizeof(t_tinychunk)), getSize(current_chunk->size));
				ft_printf("\n");
			}
			else {
				ft_printf("Status: %sFREE%s\n\n", COLOR_LIGHT_GREEN, COLOR_NC);
			}
			current_chunk = current_chunk->next;
		}

		zone_index++;
		current_zone = current_zone->previous;
	}
}

static void	printLarge(uint64_t* total_allocations, uint64_t* total_bytes) {
	if (!malloc_singleton.large)
		return ;

	t_zone*		first_zone = malloc_singleton.large->previous;
	t_zone*		current_zone = first_zone;
	uint64_t	zone_index = 1;

	ft_printf("%s=========== LARGE ===========%s\n\n", COLOR_YELLOW, COLOR_NC);

	while (current_zone != first_zone || zone_index == 1) {
		ft_printf("%s---------- Zone %d ----------%s\nSize: %lu\nReserved: %lu\nUsed: %lu\nAllocation amount: %lu\n\n", COLOR_LIGHT_GRAY, zone_index, COLOR_NC, current_zone->size, current_zone->reserved, current_zone->used, current_zone->amount);

		t_largechunk* current_chunk = getFirstChunk(current_zone);

		(*total_bytes) += current_zone->used;
		(*total_allocations) += current_zone->amount;

		ft_printf("%s########## CHUNK ###########%s\n", COLOR_LIGHT_BLUE, COLOR_NC);
		ft_printf("Status: %sALLOCATED%s\n",COLOR_LIGHT_RED, COLOR_NC);
		ft_printf("Size: %lu\n", getSize(current_chunk->size));
		ft_printf("%s~~~~~~~~~~~ DATA ~~~~~~~~~~~%s\n", COLOR_LIGHT_GRAY, COLOR_NC);
		ft_print_memory((void *)align((uint64_t)current_chunk + sizeof(t_tinychunk)), getSize(current_chunk->size));
		ft_printf("\n");

		zone_index++;
		current_zone = current_zone->previous;
	}
}

void	show_alloc_mem_ex() {
	ft_printf("\n%s<<<<<<<<<< MALLOC >>>>>>>>>>%s\n\n\n", COLOR_LIGHT_PURPLE, COLOR_NC);

	uint64_t total_allocations = 0;
	uint64_t total_bytes = 0;

	printTiny(&total_allocations, &total_bytes);
	printSmall(&total_allocations, &total_bytes);
	printLarge(&total_allocations, &total_bytes);

	if (total_allocations == 0) {
		ft_printf("--> NO HEAP ALLOCATIONS FOUND <--\n\n");
		return ;
	}

	ft_printf("%lu allocation%s\n", total_allocations, total_allocations == 1 ? "" : "s");
}
