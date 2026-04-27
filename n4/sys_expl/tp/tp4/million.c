#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 1000
void *bosser(void *);
int incremente_moi = 0;
int main(void)
{
	pthread_t th[N];
	int i;
	for (i = 0; i < N; ++i)
		pthread_create(&th[i], NULL, bosser, NULL);
	for (i = 0; i < N; ++i)
		pthread_join(th[i], NULL);

	printf("incremente_moi = %d\n", incremente_moi);
	return 0;
}
void *bosser(void *arg)
{
	for (int i = 0; i < N; ++i)
		++incremente_moi;
	return NULL;
}
