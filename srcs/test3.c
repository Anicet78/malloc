#include <stdlib.h>
#include <malloc.h>

int main(void) {
	void* test = malloc(500);
	test = realloc(test, 20);
	test = realloc(test, 40);
	test = realloc(test, 600);
	show_alloc_mem();
	free(test);
	show_alloc_mem();
}
