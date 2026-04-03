#include "malloc.h"
#include "libft.h"

int main(void) {
	char *test = ft_strdup("TEST HAHAHAHAHA");
	// ft_printf("%s\n", test);
	char* test2 = ft_strdup("ggggggggggggggggg");
	show_alloc_mem_ex();
	free(test);
	test = ft_strdup("TESTT");
	show_alloc_mem_ex();
	free(test2);
	free(test);
	show_alloc_mem_ex();
	test = ft_strdup("TESTT");
	show_alloc_mem_ex();
	free(test);
	show_alloc_mem_ex();

	for (int i = 0; i < 50000; i++) {
		char *itoa = ft_itoa(i);
		char *strjoin = ft_strjoin("TEST: ", itoa);
		free(itoa);
		// ft_printf("%s\n", strjoin);
		free(strjoin);
		char *tes = malloc(1000000000);
		(void)tes;
	}
	// show_alloc_mem_ex();
	return 0;
}
