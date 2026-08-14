#include <malloc.h>

inline size_t align(size_t size) {
	return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

size_t	calcPageSize(size_t size) {
	const bool		not_divisible = size % MALLOC_PAGE_SIZE != 0;
	const size_t	final_size = (size / MALLOC_PAGE_SIZE + not_divisible) * MALLOC_PAGE_SIZE;

	return (align(final_size));
}

void*	newRawPage(size_t size) {
	void* ptr;

	ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);

	// ft_printf("New page created: [%p - %p] (%lu bytes)\n", ptr, ptr + size - 1, size);
	return (ptr);
}
