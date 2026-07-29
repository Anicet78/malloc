#include "malloc.h"
#include "libft.h"

int main(void) {
	char *test = malloc(20);
	test[0] = '0';
	show_alloc_mem_ex();
	return 0;
}
