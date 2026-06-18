#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 8

double compute(int k);

struct worker_arg {
    int id;     // Indice du thread (0 ... NUM_THREADS - 1)
    int n;      // Taille totale du tableau
    double * results;   // Tableau partagé en écriture
};

void * worker(void *arg){
    struct worker_arg *wa = arg;
    for(int k = wa->id; k < wa->n; k += NUM_THREADS)
        wa->results[k] = compute(k);

    free(wa);   // Chaque thread libère son propre struct

    return NULL;
}

int main(int argc, char * argv[]){
    int n;
    if(argc != 2){
        fprintf(stderr, "Usage %s n\n", argv[0]);
        return 1;
    }

    if(sscanf(argv[1], "%d", &n) != 1){
        fprintf(stderr, "Argument invalide\n");
        return 1;
    }

    double * results = malloc(n * sizeof(double));
    pthread_t threads[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        struct worker_arg *wa = malloc(sizeof(struct worker_arg));
        wa->id = i;
        wa->n = n;
        wa->results = results;
        pthread_create(&threads[i], NULL, worker, wa);
    }

    for(int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    for(int i = 0; i < n; i++)
        printf("%g\n", results[i]);

    free(results);

    return 0;
}