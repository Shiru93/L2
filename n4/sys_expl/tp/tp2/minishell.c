#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAILLE_MAX 256

int main(void) {
    char ligne[TAILLE_MAX];

    while (1) {
        /* Afficher le prompt */
        printf("$ ");
        fflush(stdout);  /* forcer l'affichage avant fgets */

        /* Lire une ligne — fgets retourne NULL sur EOF (Ctrl+D) */
        if (fgets(ligne, TAILLE_MAX, stdin) == NULL) {
            printf("\n");
            return 0;
        }

        /* Remplacer '\n' par '\0' */
        ligne[strcspn(ligne, "\n")] = '\0';

        /* Ignorer les lignes vides */
        if (ligne[0] == '\0')
            continue;

        switch (fork()) {
        case -1:
            perror("fork");
            return 1;
        case 0:
            execlp(ligne, ligne, NULL);
            /* Si on arrive ici, la commande n'existe pas */
            fprintf(stderr, "%s: commande introuvable\n", ligne);
            return 127;
        default:
            wait(NULL);
        }
    }
}