/* tri_rapide_parametre.c */
/* (emprunté à Anne Canteaut) */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NB_ELEMENTS 10

void imprime_tab1(int tab[], int nb);
void imprime_tab2(char *tab[], int nb);
int comp_int(int *a, int *b);
int comp_str(char **s1, char **s2);

/** qsort est une fonction de la bibliothèque standard de C dont l'entête est
 void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))
*/

int main(){
	int *tab1;
	char *tab2[NB_ELEMENTS] = {"toto", "Auto", "auto", "titi", "a", "b", "z", "i" , "o", "d"};
	int i;

	tab1 = malloc(NB_ELEMENTS * sizeof(int));
	srand(time(NULL));
	for (i = 0 ; i < NB_ELEMENTS; i++)
		tab1[i] = random() % 1000;

	imprime_tab1(tab1, NB_ELEMENTS);
	qsort(tab1, NB_ELEMENTS, sizeof(int), comp_int);
	imprime_tab1(tab1, NB_ELEMENTS);

	imprime_tab2(tab2, NB_ELEMENTS);
	qsort(tab2, NB_ELEMENTS, sizeof(tab2[0]), comp_str);
	imprime_tab2(tab2, NB_ELEMENTS);

	return(EXIT_SUCCESS);
}

void imprime_tab1(int tab[], int nb){
	int i;
	printf("\n");
	for (i = 0; i < nb; i++)
		printf("%d \t",tab[i]);
	printf("\n");
}

void imprime_tab2(char *tab[], int nb){
	int i;
	printf("\n");
		for (i = 0; i < nb; i++)
	printf("%s \t",tab[i]);
	printf("\n");
}

int comp_int(int *a, int *b){
	return *a - *b;
}

int comp_str(char **s1, char **s2){
	return(strcmp(*s1,*s2));
}
