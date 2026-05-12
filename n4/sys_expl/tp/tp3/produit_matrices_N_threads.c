#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#ifndef N /* nombre de lignes des matrices */
#define N 10
#endif

void imprime(int matrice[N][N]);
void generation_aleatoire(int matrice[N][N]);
void *calculer_ligne(void *arg);

int A[N][N], B[N][N], R[N][N];

struct args_thread {
	int ligne; // i : le thread calcule la ligne i de R
};

int main(void)
{
	struct timespec tic, toc;
	double duree;
	int i;

	srand(time(NULL));
	generation_aleatoire(A);
	generation_aleatoire(B);
	// imprime(A);
	// puts("");
	// imprime(B);
	// puts("");
	clock_gettime(CLOCK_REALTIME, &tic);

	pthread_t th[N];
	struct args_thread args[N]; // Un struct par thread, sur la pile de main

	for (i = 0; i < N; i++) {
		args[i].ligne = i; // Initialiser AVANT pthread_create
		pthread_create(&th[i], NULL, calculer_ligne, &args[i]);
	}

	for(i = 0; i < N; i++)
		pthread_join(th[i], NULL);

	clock_gettime(CLOCK_REALTIME, &toc);
	duree = (toc.tv_sec - tic.tv_sec);
	duree += (toc.tv_nsec - tic.tv_nsec) / 1000000000.0;
	printf("durée : %g\n", duree);
	// imprime(R);
	return 0;
}

void imprime(int matrice[N][N])
{
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			printf("%d%c", matrice[i][j], j == N - 1 ? '\n' : '\t');
}

void generation_aleatoire(int matrice[N][N])
{
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			matrice[i][j] = rand() % 10;
}

void *calculer_ligne(void *arg){
	/*
	 * Copier la ligne dans une variable locale dès le début
	 * Si on gardait un pointeur vers args_thread, la variable pourrait être modifiée par main avant qu'on la lise -> piège classique
	 */
	int i = ((struct args_thread *)arg)->ligne;
	int j, k;

	for(j = 0; j < N; j++){
		R[i][j] = 0;

		for(k = 0; k < N; k++){
			R[i][j] += A[i][k] * B[k][j];
		}
	}

	/*
	 * A et B sont en lecture seule -> pas de race condition
	 * Chaque thread écrit dans une ligne différente de R -> pas de race non plus
	 */
	return NULL;
}