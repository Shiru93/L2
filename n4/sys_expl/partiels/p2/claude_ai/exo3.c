#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CAPACITE 5
#define N 10

int nb_pains = 0;   // nombre de pains actuellement dans le four

// === ZONE D'AJOUT 1 : variables de synchronisation (globales) ===
sem_t pain_dispo;
sem_t four_vide;
pthread_mutex_t mut;

void *boulanger(void *arg) {
    for (;;) {
        // === ZONE D'AJOUT 2 : attendre que le four soit vide ===
        sem_wait(&four_vide);   // Attend que le four soit complètement vide

        nb_pains = CAPACITE;
        printf("Boulanger : four rempli (%d pains)\n", nb_pains);

        // === ZONE D'AJOUT 3 : signaler que les pains sont prêts ===
        for(int i = 0; i < CAPACITE; i++)
            sem_post(&pain_dispo);  // Signale CAPACITE pains disponibles
    }
    return NULL;
}

void *client(void *arg) {
    int id = *(int *)arg;
    for (;;) {
        // === ZONE D'AJOUT 4 : prendre un pain ===
        sem_wait(&pain_dispo);
        pthread_mutex_lock(&mut);
        --nb_pains;
        int est_vide = (nb_pains == 0);
        pthread_mutex_unlock(&mut);
        if(est_vide)
            sem_post(&four_vide);

        printf("Client %d prend un pain\n", id);
    }
    return NULL;
}

int main(void) {
    // === ZONE D'AJOUT 5 : init des primitives, création des threads ===
    sem_init(&pain_dispo,  0, 0);
    sem_init(&four_vide, 0, 1);
    pthread_mutex_init(&mut, NULL);

    pthread_t boul, clients[N];
    pthread_create(&boul, NULL, boulanger, NULL);
    
    int ids[N];

    for(int i = 0; i < N; i++){
        ids[i] = i;
        pthread_create(&clients[i], NULL, client, &ids[i]);
    }

    pthread_join(boul, NULL);
    for(int i = 0; i < N; i++)
        pthread_join(clients[i], NULL);

    sem_destroy(&pain_dispo);
    sem_destroy(&four_vide);
    pthread_mutex_destroy(&mut);

    return 0;
}