/* operations_bin.c */
/* (programme emprunté à Anne Canteaut, Inria Rocquencourt) */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage(char *);
int somme(int a, int b);
int produit(int a, int b);
int difference(int a, int b);
int quotient(int a, int b);
int operateur_binaire(int a, int b, int (*f)(int, int));

int main(int argc, char *argv[])
{
	int a, b;


	if (argc != 4){
		printf("\nErreur : nombre invalide d'arguments");
		usage(argv[0]);
		return(EXIT_FAILURE);
	}
	a = atoi(argv[1]);
	b = atoi(argv[3]);
	if (strcmp(argv[2], "plus")==0){
		printf("%d\n",operateur_binaire(a,b,somme));
		return(EXIT_SUCCESS);
	}
	if (strcmp(argv[2], "fois")==0){
		printf("%d\n",operateur_binaire(a,b,produit));
		return(EXIT_SUCCESS);
	}
	if (strcmp(argv[2], "moins")==0){
		printf("%d\n",operateur_binaire(a,b,difference));
		return(EXIT_SUCCESS);
	}
	if (strcmp(argv[2], "divise_par")==0){
		printf("%d\n",operateur_binaire(a,b,quotient));
		return(EXIT_SUCCESS);
	}
	else{
		printf("\nErreur : argument(s) invalide(s)");
		usage(argv[0]);
		return(EXIT_FAILURE);
	}
}

void usage(char *cmd){
	printf("\nUsage: %s int [plus|fois|moins|divise_par] int\n",cmd);
	return;
}

int somme(int a, int b){
	return(a + b);
}

int produit(int a, int b){
	return(a * b);
}

int difference(int a, int b){
	return(a - b);
}

int quotient(int a, int b){
	return(a / b);
}

int operateur_binaire(int a, int b, int (*f)(int, int)){
	return((*f)(a,b));
}
