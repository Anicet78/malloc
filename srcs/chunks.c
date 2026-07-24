#include <malloc.h>

void*	getFirstChunk(t_zone* zone) {
	return (zone + align(sizeof(t_zone)));
}
