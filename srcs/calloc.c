#include "malloc.h"

void	*calloc(size_t nmemb, size_t size) {
	void* ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);

	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
