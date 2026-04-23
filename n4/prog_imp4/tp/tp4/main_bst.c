/*
 * main_bst.c — TP4 : Manipulation des ABR
 *
 * Exécution : ./main_bst <n>
 *   n : nombre de nœuds à insérer (lettres majuscules aléatoires)
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
 
#include "item.h"
#include "BT.h"
#include "binary_tree.h"
#include "bst.h"

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(int argc, char *argv[]){
    /* ---- Étape 1 : lire n ---- */
    if(argc != 2){
        fprintf(stderr, "Usage : %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if(n <= 0) {
        fprintf(stderr, "Erreur : n doit être > 0\n");
        return EXIT_FAILURE;
    }

    /* ---- Étape 2 : chaîne aléatoire de n majuscules ---- */
    srand((unsigned int)time(NULL));
    char *s = malloc((n + 1) * sizeof(char));
    if(!s){
        fprintf(stderr, "Erreur malloc\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < n; i++){
        s[i] = 'A' + rand() % 26; // Lettre entre 'A' et 'Z'
    }

    s[n] = '\0';

    printf("=== Chaine generee (n=%d) ===\n  \"%s\"\n\n", n, s);
 
    /* ================================================================ */
    /*  Étape 3 : insertion en FEUILLE                                  */
    /* ================================================================ */
    printf("=== Etape 3 : insertion en feuille ===\n");
 
    /* Version récursive */
    link bst_rec = NULL;
    for (int i = 0; i < n; i++)
        bst_rec = insert_BST(bst_rec, s[i]);
 
    printf("  ABR (insertion recursive) :\n");
    show_binary_tree(bst_rec, 2);
 
    /* Version itérative */
    link bst_it = NULL;
    for (int i = 0; i < n; i++)
        bst_it = insert_BST_it(bst_it, s[i]);
 
    printf("  ABR (insertion iterative) :\n");
    show_binary_tree(bst_it, 2);
 
    /* Vérification */
    if (same_tree(bst_rec, bst_it))
        printf("  OK : les deux arbres sont identiques.\n\n");
    else
        printf("  ERREUR : les arbres different !\n\n");
 
    /* ---- Étape 4 : libérer les deux arbres feuille ---- */
    delete_binary_tree(&bst_rec);
    delete_binary_tree(&bst_it);
 
    /* ================================================================ */
    /*  Étape 5 : insertion à la RACINE                                 */
    /* ================================================================ */
    printf("=== Etape 5 : insertion a la racine ===\n");
 
    /* Version récursive */
    link bst_root_rec = NULL;
    for (int i = 0; i < n; i++)
        bst_root_rec = insert_BST_root(bst_root_rec, s[i]);
 
    printf("  ABR racine (insertion recursive) :\n");
    show_binary_tree(bst_root_rec, 2);
 
    /* Version itérative */
    link bst_root_it = NULL;
    for (int i = 0; i < n; i++)
        bst_root_it = insert_BST_root_it(bst_root_it, s[i]);
 
    printf("  ABR racine (insertion iterative) :\n");
    show_binary_tree(bst_root_it, 2);
 
    /* Vérification */
    if (same_tree(bst_root_rec, bst_root_it))
        printf("  OK : les deux arbres sont identiques.\n\n");
    else
        printf("  ERREUR : les arbres different !\n\n");
 
    /* ---- Étape 6 : libérer un des deux arbres racine ---- */
    delete_binary_tree(&bst_root_rec);
    /* On garde bst_root_it pour les étapes suivantes */
 
    /* ================================================================ */
    /*  Étape 7 : supprimer le nœud de rang ⌊n/2⌋                     */
    /* ================================================================ */
    int rang = n / 2;
    link noeud = select_BST(bst_root_it, rang);
 
    if (noeud == NULL) {
        fprintf(stderr, "Erreur : select_BST a renvoye NULL\n");
        free(s);
        delete_binary_tree(&bst_root_it);
        return EXIT_FAILURE;
    }
 
    item val_a_supprimer = get_binary_tree_root(noeud);
    printf("=== Etape 7 : suppression du noeud de rang %d (valeur '%c') ===\n",
           rang, val_a_supprimer);
 
    bst_root_it = delete_node_BST(bst_root_it, val_a_supprimer);
 
    printf("  ABR apres suppression :\n");
    show_binary_tree(bst_root_it, 2);
    printf("  Taille : %d  Hauteur : %d\n\n",
           size_binary_tree(bst_root_it),
           height_binary_tree(bst_root_it));
 
    /* ================================================================ */
    /*  Étape 8 : rééquilibrage                                         */
    /* ================================================================ */
    printf("=== Etape 8 : reeequilibrage ===\n");
    printf("  Avant : hauteur = %d\n", height_binary_tree(bst_root_it));
 
    bst_root_it = balance_BST(bst_root_it);
 
    printf("  ABR reequilibre :\n");
    show_binary_tree(bst_root_it, 2);
    printf("  Apres : hauteur = %d\n\n", height_binary_tree(bst_root_it));
 
    /* ---- Étape 9 : libérer toute la mémoire ---- */
    delete_binary_tree(&bst_root_it);
    free(s);
    printf("=== Memoire liberee. Fin. ===\n");
 
    return EXIT_SUCCESS;

}