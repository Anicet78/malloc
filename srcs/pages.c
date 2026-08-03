#include <malloc.h>

size_t align(size_t size) {
	return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
}

size_t	calcPageSize(size_t size) {
	size_t page_size = sysconf(_SC_PAGESIZE);
	size_t final_size;

	if (size == 0)
		return (page_size);
	final_size = (size / page_size + (size % page_size != 0)) * page_size;
	if (final_size < size)
		return (0);
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
