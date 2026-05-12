#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define DELAI 100000000

/* ── Sémaphores de synchronisation ──────────────────────────
 * sem_a_finie : A poste, C attend
 * sem_b_finie : B poste 2 fois (C attend 1 fois, D attend 1 fois)
 * sem_c_finie : C poste, E attend
 * sem_d_finie : D poste, E attend
 * ─────────────────────────────────────────────────────────── */
sem_t sem_a_finie;
sem_t sem_b_finie;   /* valeur max 2 : C et D attendent tous les deux sur B */
sem_t sem_c_finie;
sem_t sem_d_finie;

void sleep_alea(void);
void tache_a();
void tache_b();
void tache_c();
void tache_d();
void tache_e();

/* ── Fonctions des threads ── */

void *run_a(void *arg);
void *run_b(void *arg);
void *run_c(void *arg);
void *run_d(void *arg);
void *run_e(void *arg);


int main(void)
{
	srand(time(NULL));
	
	/* Tous initialisés à 0 : personne n'a encore rien terminé */
    sem_init(&sem_a_finie, 0, 0);
    sem_init(&sem_b_finie, 0, 0);
    sem_init(&sem_c_finie, 0, 0);
    sem_init(&sem_d_finie, 0, 0);

    pthread_t ta, tb, tc, td, te;

	/* 
	 * Lancer tous les threads immédiatement :
     * C, D et E se bloqueront sur leurs sem_wait respectifs 
	 */
    pthread_create(&ta, NULL, run_a, NULL);
    pthread_create(&tb, NULL, run_b, NULL);
    pthread_create(&tc, NULL, run_c, NULL);
    pthread_create(&td, NULL, run_d, NULL);
    pthread_create(&te, NULL, run_e, NULL);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_join(tc, NULL);
    pthread_join(td, NULL);
    pthread_join(te, NULL);

    sem_destroy(&sem_a_finie);
    sem_destroy(&sem_b_finie);
    sem_destroy(&sem_c_finie);
    sem_destroy(&sem_d_finie);

	return 0;
}

void sleep_alea(void)
{
	struct timespec ts = { .tv_nsec = (rand() % 10) * DELAI };
	nanosleep(&ts, NULL);
}

void tache_a() { sleep_alea(); printf("AAAA\n"); }
void tache_b() { sleep_alea(); printf("BBBB\n"); }
void tache_c() { sleep_alea(); printf("CCCC\n"); }
void tache_d() { sleep_alea(); printf("DDDD\n"); }
void tache_e() { sleep_alea(); printf("EEEE\n"); }

void *run_a(void *arg)
{
    tache_a();
    sem_post(&sem_a_finie);   /* débloquer C (qui attend A) */
    return NULL;
}

void *run_b(void *arg)
{
    tache_b();
    sem_post(&sem_b_finie);   /* débloquer C (qui attend B) */
    sem_post(&sem_b_finie);   /* débloquer D (qui attend B) */
    return NULL;
}

void *run_c(void *arg)
{
    sem_wait(&sem_a_finie);   /* attendre A */
    sem_wait(&sem_b_finie);   /* attendre B */
    tache_c();
    sem_post(&sem_c_finie);   /* débloquer E (qui attend C) */
    return NULL;
}

void *run_d(void *arg)
{
    sem_wait(&sem_b_finie);   /* attendre B */
    tache_d();
    sem_post(&sem_d_finie);   /* débloquer E (qui attend D) */
    return NULL;
}

void *run_e(void *arg)
{
    sem_wait(&sem_c_finie);   /* attendre C */
    sem_wait(&sem_d_finie);   /* attendre D */
    tache_e();
    return NULL;
}