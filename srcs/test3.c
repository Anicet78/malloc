#include <stdlib.h>

int main(void) {
	void* test = malloc(500);
	test = realloc(test, 20);
}