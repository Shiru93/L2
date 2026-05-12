#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define COEFF_ATTENTE 100000
#define COEFF_DELTA   5000

void *compteur1(void *);
void *compteur2(void *);
void prendre_du_temps_pour_compter();

/* 2 sémaphores : un par thread pour signaler qu'il a fini son pas */
sem_t sem_a;  /* th1 poste ici, th2 attend ici */
sem_t sem_b;  /* th2 poste ici, th1 attend ici */

int main(void)
{
	pthread_t th1, th2;

	/* Initialisés à 0 : personne n'a encore fini son premier pas */
    sem_init(&sem_a, 0, 0);
    sem_init(&sem_b, 0, 0);

	if (pthread_create(&th1, NULL, compteur1, NULL) != 0) {
		perror("create th1");
		return 1;
	}
	if (pthread_create(&th2, NULL, compteur2, NULL) != 0) {
		perror("create th2");
		return 1;
	}

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	sem_destroy(&sem_a);
    sem_destroy(&sem_b);

	return 0;
}

void *compteur1(void *sem_tab)
{
	int i;
	for (i = 0; i <= 100; i = i + 1) {
		prendre_du_temps_pour_compter();
		printf("a : %d\n", i);
		sem_post(&sem_a);	/* signaler à th2 : j'ai affiché mon i */
		sem_wait(&sem_b);	/* attendre que th2 ait aussi affiché son i */
	}
	return NULL;
}

void *compteur2(void *sem_tab)
{
	int i;
	for (i = 0; i <= 100; i = i + 1) {
		prendre_du_temps_pour_compter();
		printf("b : %d\n", i);
		sem_post(&sem_b);   /* signaler à th1 : j'ai affiché mon i */
        sem_wait(&sem_a);   /* attendre que th1 ait aussi affiché son i */
	}
	return NULL;
}

void prendre_du_temps_pour_compter()
{
	struct timespec ts = { .tv_nsec = (COEFF_ATTENTE + (rand() % 10) *
			COEFF_DELTA ) * 1000 };
	nanosleep(&ts, NULL);
}
