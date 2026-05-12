#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 1000

void *bosser(void *);

int incremente_moi = 0;
sem_t verrou;

int main(void)
{
	pthread_t th[N];
	int i;

	sem_init(&verrou, 0, 1);

	for (i = 0; i < N; ++i)
		pthread_create(&th[i], NULL, bosser, NULL);

	for (i = 0; i < N; ++i)
		pthread_join(th[i], NULL);

	sem_destroy(&verrou);
	printf("incremente_moi = %d\n", incremente_moi);
	return 0;
}

void *bosser(void *arg)
{
	for (int i = 0; i < N; ++i){
		sem_wait(&verrou);
		++incremente_moi;
		sem_post(&verrou);
	}	

	return NULL;
}
