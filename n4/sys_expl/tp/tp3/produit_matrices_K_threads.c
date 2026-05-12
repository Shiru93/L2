#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#ifndef N
#define N 1000
#endif

#ifndef K
#define K 4
#endif

int A[N][N], B[N][N], R[N][N];

void imprime(int matrice[N][N]);
void generation_aleatoire(int matrice[N][N]);
void *calculer_lignes(void *arg);

struct args_thread {
    int d;   /* numéro du thread : calcule les lignes d, d+K, d+2K, ... */
};



int main(void)
{
    struct timespec tic, toc;
    double duree;
    int d;

    srand(time(NULL));
    generation_aleatoire(A);
    generation_aleatoire(B);

    clock_gettime(CLOCK_REALTIME, &tic);

    pthread_t th[K];
    struct args_thread args[K];

    for (d = 0; d < K; d++) {
        args[d].d = d;
        pthread_create(&th[d], NULL, calculer_lignes, &args[d]);
    }

    for (d = 0; d < K; d++)
        pthread_join(th[d], NULL);

    clock_gettime(CLOCK_REALTIME, &toc);
    duree  = (toc.tv_sec  - tic.tv_sec);
    duree += (toc.tv_nsec - tic.tv_nsec) / 1000000000.0;
    printf("K=%d, durée : %g\n", K, duree);

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

void *calculer_lignes(void *arg) {
    /* Copier d localement dès le début → pas de dépendance vers la pile de main */
    int d = ((struct args_thread *)arg)->d;
    int i, j, k;

    /* Thread d calcule les lignes d, d+K, d+2K, ... jusqu'à N-1 */
    for (i = d; i < N; i += K) {
        for (j = 0; j < N; j++) {
            R[i][j] = 0;
            for (k = 0; k < N; k++)
                R[i][j] += A[i][k] * B[k][j];
        }
    }
    return NULL;
}