/*
 * main_llrbt.c — TP5 : Tri par LLRBT
 *
 * Exécution : ./main_llrbt <n>
 *
 * Le programme :
 *   1. Lit n depuis la ligne de commande.
 *   2. Remplit t[0..n-1] avec des entiers aléatoires entre 0 et 99.
 *   3. Construit un LLRBT en insérant t[0], t[1], ..., t[n-1].
 *   4. Parcourt le LLRBT en infixe pour réécrire t en ordre croissant.
 *   5. Libère la mémoire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "llrbt.h"

/* ------------------------------------------------------------------ */
/*  Affiche un tableau d'entiers                                       */
/* ------------------------------------------------------------------ */
static void print_array(const item *t, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("]\n");
}

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(int argc, char *argv[]) {

    /* ---- Étape 1 : lire n ---- */
    if (argc != 2) {
        fprintf(stderr, "Usage : %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Erreur : n doit etre > 0\n");
        return EXIT_FAILURE;
    }

    /* ---- Étape 2 : tableau aléatoire 0..99 ---- */
    item *t = malloc(n * sizeof(item));
    if (!t) { fprintf(stderr, "Erreur malloc\n"); return EXIT_FAILURE; }

    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
        t[i] = rand() % 100;

    printf("=== Tableau initial (n=%d) ===\n  ", n);
    print_array(t, n);

    /* ---- Étape 3 : construire le LLRBT ---- */
    llrbt_link arbre = NULL;
    for (int i = 0; i < n; i++)
        arbre = insert_LLRBT(arbre, t[i]);

    /* Forcer la racine à être noire (règle 4) */
    if (arbre != NULL)
        arbre->color = BLACK;

    printf("\n=== LLRBT construit ===\n");
    printf("  (R = lien rouge entrant, . = lien noir)\n\n");
    show_llrbt(arbre, 0);
    printf("\n");

    /* ---- Étape 4 : parcours infixe → tableau trié ---- */
    int idx = 0;
    inorder_LLRBT(arbre, t, &idx);

    printf("=== Tableau apres tri par LLRBT ===\n  ");
    print_array(t, n);

    /* Vérification que le tableau est bien trié */
    int ok = 1;
    for (int i = 0; i < n - 1; i++)
        if (t[i] > t[i + 1]) { ok = 0; break; }
    printf("  Verification : %s\n\n", ok ? "OK tri croissant" : "ERREUR");

    /* ---- Étape 5 : libérer la mémoire ---- */
    delete_llrbt(&arbre);
    free(t);
    printf("=== Memoire liberee. Fin. ===\n");

    return EXIT_SUCCESS;
}
