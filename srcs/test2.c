#include "malloc.h"
#include "libft.h"

int main(void) {
	char *test = MyMalloc(16);
	if (!test) {
		ft_printf("%sMALLOC FAILED%s\n", COLOR_LIGHT_RED, COLOR_NC);
		return 1;
	}
	char *test2 = MyMalloc(16);
	test[0] = 'A';
	test[15] = 'B';
	test2[15] = 'C';
	MyFree(test);
	show_alloc_mem_ex();
	return 0;
}
