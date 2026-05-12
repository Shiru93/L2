#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> 

#define N_DFT 8

void *somme(void *arg);
void *produit(void *arg);

int main(int argc, char *argv[])
{
    int n = argc < 2 ? N_DFT : atoi(argv[1]);

    pthread_t th_somme, th_produit;

    /* Lancer les deux threads en parallèle */
	if(pthread_create(&th_somme,   NULL, somme,   &n)){
		perror("pthread_create somme");
		return 1;
	}
    
	if(pthread_create(&th_produit, NULL, produit, &n)){
		perror("pthread_create produit");
		return 1;
	}
    

    /* Récupérer les résultats via pthread_join */
    void *res_s, *res_p;
    pthread_join(th_somme,   &res_s);
    pthread_join(th_produit, &res_p);

	/*
	 * intptr_t — un entier de la même taille qu'un pointeur
	 * Sur un système 32 bits, les pointeurs font 4 octets → intptr_t = entier de 4 octets.
	 * Sur un système 64 bits, les pointeurs font 8 octets → intptr_t = entier de 8 octets.
	 * Pourquoi en a-t-on besoin ici ?
	 * Les threads communiquent uniquement via void * (un pointeur générique). On veut transporter un simple int dedans :
	 * void * = 8 octets (sur 64 bits)
	 * int    = 4 octets
	 * 
	 * → on ne peut pas mettre un int directement dans void* sans risque de troncature
	 * 
	 * int res = 42;

	 * int → void*  (pour return dans le thread)
 	 * return (void *)(intptr_t)res;
	 *					↑
	 * 				int(4) → intptr_t(8) → void*(8) : pas de perte

	 * void* → int  (pour récupérer dans main)
	 * int s = (intptr_t)res_s;
	 *          ↑
	 *    void*(8) → intptr_t(8) → int(4) : troncature contrôlée
	 * 
	 * Pour un simple int comme ici, l'astuce intptr_t est acceptable. Pour des données plus complexes, utilise toujours malloc.
	 */

    int s = (intptr_t)res_s;
    int p = (intptr_t)res_p;

    printf("n : %d, somme : %d, produit : %d\n", n, s, p);
    return 0;
}

void *somme(void *arg){
    int n = *(int *)arg;   /* recaster void* → int* puis déréférencer */
    int i, res = 0;
    for (i = 1; i <= n; ++i)
        res += i;
    return (void *)(intptr_t)res;  /* emballer le résultat dans void* */
}

void *produit(void *arg){
    int n = *(int *)arg;
    int i, res = 1;
    for (i = 1; i <= n; ++i)
        res *= i;
    return (void *)(intptr_t)res;
}

/*
void *somme(void *n) {
	int i, num = *((int *) n);
	int *res = malloc(sizeof(int));

	*res = 0;

	for (i = 1; i <= num; ++i)
		*res += i;

	return res;
}
void *produit(void *n) {
	int i, num = *((int *) n);
	int *res = malloc(sizeof(int));

	*res = 1;
	
	for (i = 1; i <= num; ++i)
		*res *= i;
	
	return res;
}
*/