#include "malloc.h"

int main(void) {
	void* test = malloc(10);
	show_alloc_mem_ex();
	printf("%p\n", test);
	return 0;
}