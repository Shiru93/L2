#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAILLE_MAX 256
#define ARGS_MAX   64

/*
 * Découpe la ligne en tokens séparés par des espaces.
 * Retourne le nombre d'arguments.
 * Remplit args[] et met args[n] = NULL (format execvp).
 * Remplit *background = 1 si le dernier token est "&".
 */
int parser(char *ligne, char *args[], int *background) {
    int n = 0;
    *background = 0;

    char *token = strtok(ligne, " ");
    while (token != NULL && n < ARGS_MAX - 1) {
        args[n++] = token;
        token = strtok(NULL, " ");
    }
    args[n] = NULL;  /* sentinelle pour execvp */

    /* Détecter & en dernier argument */
    if (n > 0 && strcmp(args[n - 1], "&") == 0) {
        *background = 1;
        args[n - 1] = NULL;  /* retirer le & des arguments */
        n--;
    }

    return n;
}

int main(void) {
    char ligne[TAILLE_MAX];
    char *args[ARGS_MAX];
    int background;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(ligne, TAILLE_MAX, stdin) == NULL) {
            printf("\n");
            return 0;
        }

        /* Supprimer le '\n' final */
        ligne[strcspn(ligne, "\n")] = '\0';

        int n = parser(ligne, args, &background);

        /* Ignorer les lignes vides */
        if (n == 0)
            continue;

        /* ── Commandes internes ── */

        /* exit */
        if (strcmp(args[0], "exit") == 0)
            return 0;

        /* pwd : afficher le répertoire courant */
        if (strcmp(args[0], "pwd") == 0) {
            char cwd[TAILLE_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                printf("%s\n", cwd);
            else
                perror("pwd");
            continue;
        }

        /* cd : changer de répertoire */
        if (strcmp(args[0], "cd") == 0) {
            /* cd sans argument → aller dans HOME */
            const char *dest = args[1] ? args[1] : getenv("HOME");
            if (chdir(dest) != 0)
                perror("cd");
            continue;
        }

        /* ── Commande externe ── */
        switch (fork()) {
        case -1:
            perror("fork");
            return 1;

        case 0:
            execvp(args[0], args);
            fprintf(stderr, "%s: commande introuvable\n", args[0]);
            return 127;

        default:
            if (!background)
                wait(NULL);
            /* Si background : on n'attend pas, on reboucle immédiatement */
        }
    }
}