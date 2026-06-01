#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct worker_arg {
    int id;             // Indice du thread
    int n ;             // Taille totale
    int t;              // Nombre de threads
    double resultat;    // Résultat partiel (rempli par le thread)
};

void * worker(void *arg);

int main(void){
    int n = 1000000, t = 8;
    pthread_t threads[t];
    struct worker_arg args[t];

    for(int i = 0; i < t; i++){
        args[i] = (struct worker_arg){.id = i, .n = n, .t = t, .resultat = 0.0};
        if(pthread_create(&threads[i], NULL, worker, &args[i]) != 0){
            perror("pthread_create");
            return 1;
        }
    }

    double total = 0.0;
    for(int i = 0; i < t; i++){
        pthread_join(threads[i], NULL);
        total += args[i].resultat;
    }

    printf("Somme = %g\n", total);

    return 0;
}

void * worker(void *arg){
    struct worker_arg *wa = (struct worker_arg *) arg;
    wa->resultat = 0.0;

    for(int k = wa->id; k < wa->n; k += wa->t)
        wa->resultat += f(k);

    return NULL;    // La valeur se récupère via wa->resultat après pthreead_join
}