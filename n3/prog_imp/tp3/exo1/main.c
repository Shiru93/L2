#include "fonctions.h"

#define TAILLE_TAB1 15
#define TAILLE_TAB2 35

#define TAILLE_MATRICE 10

#define TAILLE_VECTEUR 20
#define TAILLE_POIDS 20

int main(){
    int * tab1 = allouer_tab(TAILLE_TAB1);
    int * tab2 = allouer_tab(TAILLE_TAB2);
    int * vecteur = allouer_tab(TAILLE_VECTEUR);
    int * poids = allouer_tab(TAILLE_POIDS);
    int element, capacite, test;
    int ** A = allouer_matrice(TAILLE_MATRICE);
    int ** B = allouer_matrice(TAILLE_MATRICE);
    int ** C = allouer_matrice(TAILLE_MATRICE);

    srand(time(NULL));

    generer_tab(tab1, TAILLE_TAB1);
    generer_tab(tab2, TAILLE_TAB2);

    printf("Affichage des tableaux avant le tri par sélection :\n");
    printf("tab1 :\n");
    afficher_tab(tab1, TAILLE_TAB1);
    printf("\ntab2 :\n");
    afficher_tab(tab2, TAILLE_TAB2);

    tri_selection(tab1, TAILLE_TAB1);
    tri_selection(tab2, TAILLE_TAB2);

    printf("Affichage des tableaux après le tri par sélection :\n");
    printf("tab1 :\n");
    afficher_tab(tab1, TAILLE_TAB1);
    printf("\ntab2 :\n");
    afficher_tab(tab2, TAILLE_TAB2);

    printf("Veuillez taper le nombre que vous recherchez : ");
    scanf("%d", &element);

    int r1 = recherche_iterative(tab1, TAILLE_TAB1, element);
    int r2 = recherche_dichotomique(tab2, TAILLE_TAB2, element);

    switch ((r1 != -1) * 2 + (r2 != -1)) {
        case 0:
            printf("%d n'est présent dans aucun tableau\n", element);
            break;
        case 1:
            printf("%d présent dans tab2 (indice %d)\n", element, r2);
            break;
        case 2:
            printf("%d présent dans tab1 (indice %d)\n", element, r1);
            break;
        case 3:
            printf("%d présent dans tab1 (indice %d) et tab2 (indice %d)\n", element, r1, r2);
            break;
    }

    printf("\n");

    generer_matrice(A, TAILLE_MATRICE);
    generer_matrice(B, TAILLE_MATRICE);

    printf("Matrice A :\n");
    afficher_matrice(A, TAILLE_MATRICE);

    printf("\n");

    printf("Matrice B :\n");
    afficher_matrice(B, TAILLE_MATRICE);

    printf("\n");

    multiplier_matrice(A, B, C, TAILLE_MATRICE);

    printf("Matrice C : \n");
    afficher_matrice(C, TAILLE_MATRICE);

    printf("\n");
    printf("Le trajet minimal entre 4 points est : %d\n",trajet_minimal_4_points(A, TAILLE_MATRICE));

    capacite = rand() % 1000;

    printf("\nCapacité : %d\n", capacite);

    generer_tab(poids, TAILLE_POIDS);
    printf("\nPoids = ");
    afficher_vecteur(poids, TAILLE_POIDS);

    generer_vecteur(vecteur, TAILLE_VECTEUR);
    printf("\nVecteur = ");
    afficher_vecteur(vecteur, TAILLE_VECTEUR);

    test = test_sac_a_dos(poids, TAILLE_POIDS, capacite, vecteur);

    if(test != -1){
        printf("Le poids total des pépites choisies est de : %d grammes\n", test);
    }

    enum_vecteur(TAILLE_VECTEUR, vecteur, 0);

    return 0;
}