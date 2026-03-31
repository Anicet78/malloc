#include "malloc.h"
#include "libft.h"

int main(void) {
	char *test = ft_strdup("TEST");
	// ft_printf("%s\n", test);
	test = ft_strdup("bbbababababba");
	show_alloc_mem_ex();
	return 0;
}
