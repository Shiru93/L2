#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include "chemin.h"

int main(int argc, char * argv[]){
    FILE * f;
    int **tab;
    char * palette[9] = {" ", "*", "2", "3", "4", "v", "^", ">", "<"};
    int n = 0;

    if (argc != 2) {
        fprintf(stderr, "Trop ou pas assez d'arguments\n");
        return EXIT_FAILURE;
    }

    if((f = fopen(argv[1], "r")) != NULL) {
        fprintf(stderr, "Le fichier existe\n");
        fprintf(stderr, "Fichier : %s ouvert\n", argv[1]);

        lit_fichier(argv[1], &tab, &n);
        afficher_lab(tab, n, palette);
        printf("\n");

    if (chercher_chemin(tab, n)) {
        printf("Chemin trouve!\n");
        afficher_lab(tab, n, palette);
    } else {
        printf("Aucun chemin trouve.\n");
    }

        for(int i = 0; i < n; i++) free(tab[i]);
        free(tab);
        
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Le fichier n'existe pas\n");
        return EXIT_FAILURE;
    }

    return 0;
}