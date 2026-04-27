#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define N 5
#define COEFF_ATTENTE 50000

/* attendre delai microsecondes */
void microsleep(int delai);

void work(void);

void *chiffres_et_alphabet(void *);

int main(void)
{
	int i, nums[N];
	pthread_t th[N];
	srand(time(NULL));

	for (i = 0; i < N; ++i) {
		nums[i] = i;
		if (pthread_create(&th[i], NULL, chiffres_et_alphabet, &nums[i]) != 0) {
			perror("create");
			return 1;
		}
	}

	for (i = 0; i < N; ++i)
		pthread_join(th[i], NULL);
	return 0;
}

void *chiffres_et_alphabet(void *arg)
{
	int i = *((int *) arg);
	printf("%d\n", i);
	printf("%c\n", 'A' + i);
	return NULL;
}

void work(void) { microsleep((rand() % 10) * COEFF_ATTENTE); }

void microsleep(int delai)
{
	struct timespec ts = { .tv_sec = delai / 1000000,
		.tv_nsec = 1000 * (delai % 1000000)  };
	nanosleep(&ts, NULL);
}
