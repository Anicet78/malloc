#include "malloc.h"
#include "libft.h"
#include <sys/time.h>

long	get_time(struct timeval *timestamp)
{
	long	time;

	time = timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000;
	return (time);
}

long	get_time_now(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (get_time(&timestamp));
}

int main(void) {
	long start = get_time_now();

	char *test = ft_strdup("TEST HAHAHAHAHA");
	// ft_printf("%s\n", test);
	char* test2 = ft_strdup("ggggggggggggggggg");
	// show_alloc_mem();
	free(test);
	test = ft_strdup("TESTT");
	// show_alloc_mem();
	free(test2);
	free(test);
	// show_alloc_mem();
	test = ft_strdup("TESTT");
	// show_alloc_mem();
	free(test);
	// show_alloc_mem();

	for (int i = 0; i < 50000; i++) {
		char *itoa = ft_itoa(i);
		char *strjoin = ft_strjoin("TEST: ", itoa);
		free(itoa);
		// ft_printf("%s\n", strjoin);
		free(strjoin);
		char *tes = malloc(1000000000);
		(void)tes;
	}

	long end = get_time_now();
	printf("%ld ms\n", end - start);
	// show_alloc_mem();
	return 0;
}
