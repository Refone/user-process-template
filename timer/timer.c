#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main()
{
	char c;
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);

	while (1)
	{
		c = getchar();
		gettimeofday(&t2, NULL);
		printf("[LRF-TIMER] %d sec %d usec\n", t2.tv_sec, t2.tv_usec);
	}

	return 0;
}
