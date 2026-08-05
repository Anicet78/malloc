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

	for (int i = 0; i < 100000; i++) {
		int sizes[6] = {42, 31, 921, 177, 19778, 159701};

		unsigned int i = arc4random() % 6;
		char *test = malloc(sizes[i]);
		memset(test, 0, sizes[i]);

		i = arc4random() % 3;
		if (i == 1)
			free(test);
	}

	long end = get_time_now();
	ft_printf("%ld ms\n", end - start);
	// show_alloc_mem();
	return 0;
}
