#include "malloc.h"
#include "libft.h"

int main(void) {
	char *test = malloc(1600);
	if (!test) {
		ft_printf("%sMALLOC FAILED%s\n", COLOR_LIGHT_RED, COLOR_NC);
		return 1;
	}
	char *test2 = malloc(1600);
	test[0] = 'A';
	test[15] = 'B';
	test2[15] = 'C';
	// free(test);
	// free(test2);
	show_alloc_mem();
	return 0;
}
