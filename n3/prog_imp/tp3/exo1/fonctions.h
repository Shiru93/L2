#ifndef _FONCTIONS_H
#define _FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tri par sékecction
int * allouer_tab(int n);
void generer_tab(int * tab, int n);
void tri_selection(int * tab, int n);
void afficher_tab(int * tab, int n);

// Recherche cursive et recherche dichotomique
int recherche_iterative(int * tab, int n, int element);
int recherche_dichotomique(int *tab, int n, int element);
int recherche_dichotomique_recursive(int *tab, int debut, int fin, int element);

// Matrices
int ** allouer_matrice(int n);
void generer_matrice(int ** mat, int n);
void afficher_matrice(int ** mat, int n);
void multiplier_matrice(int ** A, int ** B, int ** C, int n);
void liberer_matrice(int **mat, int n);

// Trajet minimal entre 4 points
int trajet_minimal_4_points(int **M, int n);

//Remplir son sac à dos
void generer_vecteur(int * tab, int n);
int test_sac_a_dos(int *poids, int n, int capacite, int *vecteur);
void afficher_vecteur(int * vecteur, int n);
void enum_vecteur(int n, int * vecteur, int position);

#endif