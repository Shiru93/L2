#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void lit_fichier(char * nomfic, int *** lab, int * n){
    FILE * f;
    int x;

    if((f = fopen(nomfic, "r")) != NULL){
        fscanf(f, "%d", n);
        printf("Taille : %d\n", *n);
    } else {
        fprintf(stderr, "Le fichier n'existe pas\n");
        return;
    }

    *lab = malloc(sizeof(int *) * (*n));
    if(!(*lab)){
        fprintf(stderr, "Erreur allocation mémoire\n");
        return;
    }
    
    for(int i = 0; i < *n; i++){
        (*lab)[i] = malloc(sizeof(int) * (*n));
        if(((*lab)[i]) == NULL){
            fprintf(stderr, "Erreur allocation mémoire ligne %d\n", i);
            return;
        }
    }

    // for(int i = 0; i < *n; i++){
    //     for(int j = 0; j < *n; j++){
    //         if(fgetc(f) != 1) {
    //             fprintf(stderr, "Erreur de lecture position (%d, %d)\n", i, j);
    //             return;
    //         }
    //     }
    // }

    printf("Matrice lue :\n");
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            x = fgetc(f);

            while(x == ' ' || x == '\n' || x == '\t' || x == '\r'){
                x = fgetc(f);
            }

            (*lab)[i][j] = x - '0';
            
            // printf("%d ", (*lab)[i][j]);     
        }
        // printf("\n");
    }

    fclose(f);
}

void afficher_lab(int ** lab, int n, char ** palette){
    printf("+");
    for(int i = 0; i < n; i++) printf("-");
    printf("+\n");

    for(int i = 0; i < n; i++){
        printf("|");
        for(int j = 0; j < n; j++){
            printf("%c", palette[lab[i][j]][0]);
        }
        printf("|\n");
    }

    printf("+");
    for(int i = 0; i < n; i++) printf("-");
    printf("+\n");
}