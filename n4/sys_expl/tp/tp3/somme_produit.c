#include <stdio.h>
#include <stdlib.h>

#define N_DFT 8

/* Retourne la somme 1 + ... + n */
int somme(int n);

/* Retourne le produit 1 * ... * n */
int produit(int n);

int main(int argc, char *argv[])
{
	int n = argc < 2 ? N_DFT : atoi(argv[1]);
	
	int s = somme(n);
	int p = produit(n);
	printf("n : %d, somme : %d, produit : %d\n", n, s, p);
	return 0;
}

int somme(int n)
{
	int i, res = 0;
	for (i = 1; i <= n; ++i)
		res += i;
	return res;
}

int produit(int n)
{
	int i, res = 1;
	for (i = 1; i <= n; ++i)
		res *= i;
	return res;
}
