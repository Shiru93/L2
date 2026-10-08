#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

void tache_A(void);
void tache_B(void);
void tache_C(void);
void tache_D(void);
void tache_E(void);
void tache_F(void);

// Sémaphores : initialisés à 0, signalés quand la tâche est finie
static sem_t sem_A, sem_B, sem_C, sem_D, sem_E, sem_F;

void *run_A(void *arg){
    tache_A();
    printf("Tâche A terminée\n");
    sem_post(&sem_A);
    
    return NULL;
}

void *run_B(void *arg){
    tache_B();
    printf("Tâche B terminée\n");
    sem_post(&sem_B);
    
    return NULL;
}

void *run_C(void *arg){
    tache_C();
    printf("Tâche C terminée\n");
    sem_post(&sem_C);
    sem_post(&sem_C);   // Consommé par D et E
    
    return NULL;
}

void *run_D(void *arg){
    sem_wait(&sem_A);
    sem_wait(&sem_B);
    sem_wait(&sem_C);   // Attend aussi C
    tache_D();
    printf("Tâche D terminée\n");
    sem_post(&sem_D);
    
    return NULL;
}

void *run_E(void *arg){
    sem_wait(&sem_C);
    tache_E();
    printf("Tâche E terminée\n");
    sem_post(&sem_E);
    
    return NULL;
}

void *run_F(void *arg){
    sem_wait(&sem_D);
    sem_wait(&sem_E);
    tache_F();
    printf("Tâche F terminée\n");
    sem_post(&sem_F);
    
    return NULL;
}

int main(void){
    sem_init(&sem_A, 0, 0);
    sem_init(&sem_B, 0, 0);
    sem_init(&sem_C, 0, 0);
    sem_init(&sem_D, 0, 0);
    sem_init(&sem_E, 0, 0);

    pthread_t tA, tB, tC, tD, tE, tF;
    pthread_create(&tA, NULL, run_A, NULL);
    pthread_create(&tB, NULL, run_B, NULL);
    pthread_create(&tC, NULL, run_C, NULL);
    pthread_create(&tD, NULL, run_D, NULL);
    pthread_create(&tE, NULL, run_E, NULL);
    pthread_create(&tF, NULL, run_F, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);
    pthread_join(tD, NULL);
    pthread_join(tE, NULL);
    pthread_join(tF, NULL);

    sem_destroy(&sem_A);
    sem_destroy(&sem_B);
    sem_destroy(&sem_C);
    sem_destroy(&sem_D);
    sem_destroy(&sem_E);
}


/*
 * Question 3
 * Problème : printf n'est pas atomique. 
 *            Deux threads peuvent écrire simultanément et leurs caractères peuvent d'entremêler
 * Solution : Protéger chaque printf par un mutex global
 * 
 * static pthread_mutex_t mutex_print;
 * // Dans main, avant pthread_create :
 * pthread_mutex_init(&mutex_print, NULL);
 * // Chaque printf devient :
 * pthread_mutex_lock(&mutex_print);
 * printf("Tâche X terminée\n");
 * pthread_mutex_unlock(&mutex_print);
 * // Et en fin de main :
 * pthread_mutex_destroy(&mutex_print);
 * 
 * Cela garantit qu'un seul thread écrit à la fois, sans bloquer le parallélisme (le mutex n'est tenu que le temps de l'appel printf);
 */