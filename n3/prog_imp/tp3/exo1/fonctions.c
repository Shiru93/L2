#include "fonctions.h"

int * allouer_tab(int n){
    return malloc(sizeof(int) * n);
}

void generer_tab(int * tab, int n){
    for(int i = 0; i < n; i++)
        tab[i] = rand() % 100;
}

void tri_selection(int *tab, int n){
    for(int i = 0; i < n - 1; i++){
        int min_index = i;
        for(int j = i + 1; j < n; j++)
            if(tab[j] < tab[min_index])
                min_index = j;

        int temp = tab[i];
        tab[i] = tab[min_index];
        tab[min_index] = temp;
    }
}

void afficher_tab(int * tab, int n){
    for(int i = 0; i < n; i++)
        printf("tab[%d] = %d\n", i, tab[i]);
}

int recherche_iterative(int * tab, int n, int element){
    for(int i = 0; i < n; i++)
        if(tab[i] == element) return i;

    return -1;
}

int recherche_dichotomique(int *tab, int n, int element) {
    return recherche_dichotomique_recursive(tab, 0, n-1, element);
}

int recherche_dichotomique_recursive(int *tab, int debut, int fin, int element){
    if(debut > fin) return -1;

    int milieu = (debut + fin) / 2;

    if(tab[milieu] == element) return milieu;
    else if(tab[milieu] > element) return recherche_dichotomique_recursive(tab, debut, milieu - 1, element);
    else return recherche_dichotomique_recursive(tab, milieu + 1, fin, element);
}

int ** allouer_matrice(int n){
    if (n <= 0) {
        printf("Erreur: taille de matrice invalide\n");
        return NULL;
    }

    int ** mat = malloc(n * sizeof(int *));
    if (mat == NULL) {
        printf("Erreur d'allocation mémoire pour les lignes\n");
        return NULL;
    }

    for(int i = 0; i < n; i++){
        mat[i] = malloc(n * sizeof(int));
        if (mat[i] == NULL) {
            printf("Erreur d'allocation mémoire pour la ligne %d\n", i);
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }

            free(mat);

            return NULL;
        }
    }

    return mat;
}

void generer_matrice(int ** mat, int n){
    if(mat == NULL) {
        printf("Erreur : la matrice n'est pas allouée");
        return;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = rand() % 100;
        }
    }
}

void afficher_matrice(int ** mat, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d\t", mat[i][j]);
        }

        printf("\n");
    }
}

void multiplier_matrice(int ** A, int ** B, int ** C, int n){
    if (A == NULL || B == NULL || C == NULL) {
        printf("Erreur: matrices non allouées\n");
        return;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = A[i][j] * B[i][j];
        }
    }
}

void liberer_matrice(int **mat, int n) {
    if (mat == NULL) return;
    
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

int trajet_minimal_4_points(int **M, int n) {
    if (n < 4) {
        printf("Erreur: besoin d'au moins 4 lieux (n=%d)\n", n);
        return -1;
    }
    
    if (M == NULL) {
        printf("Erreur: matrice non allouée\n");
        return -1;
    }
    
    int temps_minimal = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                
                for (int l = 0; l < n; l++) {
                    if (l == i || l == j || l == k) continue;
                    
                    int temps_circuit = M[i][j] + M[j][k] + M[k][l] + M[l][i];
                    
                    if (temps_minimal == -1 || temps_circuit < temps_minimal) {
                        temps_minimal = temps_circuit;
                    }
                }
            }
        }
    }
    
    return temps_minimal;
}

void generer_vecteur(int * tab, int n){
    for(int i = 0; i < n; i++)
        tab[i] = rand()% 2;
}

int test_sac_a_dos(int *poids, int n, int capacite, int *vecteur) {
    int poids_total = 0;
    
    for (int i = 0; i < n; i++) {
        if (vecteur[i] == 1) {
            poids_total += poids[i];
        }
    }
    
    if (poids_total > capacite) {
        return -1;
    }
    
    return poids_total;
}

void afficher_vecteur(int * vecteur, int n){
    printf("[");
    for(int i = 0; i < n; i++){
        printf("%d", vecteur[i]);
        if(i != n - 1) printf(", ");
    }
    printf("]\n");
}

void enum_vecteur(int n, int * vecteur, int position){
    if(position == n)
        afficher_vecteur(vecteur, n);

    else {
        vecteur[position] = 0;
        enum_vecteur(n, vecteur, position + 1);
        vecteur[position] = 1;
        enum_vecteur(n, vecteur, position + 1);
    }
}