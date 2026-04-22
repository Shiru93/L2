/*
 * main_expr.c
 * TP2 — Analyse et évaluation d'expressions arithmétiques préfixes
 *
 * Une expression arithmétique PRÉFIXE (ou notation polonaise) place
 * l'opérateur AVANT ses deux opérandes. Exemples :
 *
 *   Infixe  : (3 * 4) + 5
 *   Préfixe : + * 3 4 5
 *
 *   Infixe  : (8 - 2) / (1 + 2)
 *   Préfixe : / - 8 2 + 1 2
 *
 * L'arbre syntaxique (AST) correspondant à "+ * 3 4 5" est :
 *
 *        +
 *       / \
 *      *   5
 *     / \
 *    3   4
 *
 * Chaque nœud interne est un opérateur, chaque feuille est un chiffre.
 * Le type `item` est `char` (cf. item.h) : chaque nœud stocke donc
 * exactement UN caractère.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "BT.h"
#include "binary_tree.h"
#include "fonctions.h"

/* ------------------------------------------------------------------ */
/*  main                                                               */
/* ------------------------------------------------------------------ */
int main(void) {
    char expr[256];
    char buf_prefixe[256];
    char buf_infixe[256];
 
    /* Étape 1 : lire l'expression */
    printf("Entrer une expression arithmétique préfixe\n");
    printf("(ex : + * 3 4 5    ou   / - 8 2 + 1 2)\n> ");
    fgets(expr, sizeof(expr), stdin);
 
    int len = strlen(expr);
    if (len > 0 && expr[len - 1] == '\n') {
        expr[len - 1] = '\0';
        len--;
    }
    printf("\n=== Expression lue ===\n  \"%s\"\n", expr);
 
    /* Étape 2 : construire et afficher l'arbre */
    int pos = 0;
    link ast = parse_expr(expr, &pos);
    printf("\n=== Arbre syntaxique ===\n\n");
    show_binary_tree(ast, 0);
    printf("\n  Taille : %d noeuds   Hauteur : %d\n",
           size_binary_tree(ast), height_binary_tree(ast));
 
    /* Étape 3 : évaluer */
    printf("\n=== Evaluation ===\n  %s  =  %d\n", expr, eval_tree(ast));
 
    /* Étape 4 : reconstruire en préfixe */
    int wpos = 0;
    tree_to_expr(ast, buf_prefixe, &wpos);
    buf_prefixe[wpos] = '\0';
    printf("\n=== Reconstruction prefixe ===\n  \"%s\"\n", buf_prefixe);
    if (strcmp(expr, buf_prefixe) == 0)
        printf("  OK : identique a l'original.\n");
    else
        printf("  ERREUR : different de l'original !\n");
 
    /* Étape 5 (TP3) : reconstruire en infixe */
    wpos = 0;
    tree_to_infix(ast, buf_infixe, &wpos);
    buf_infixe[wpos] = '\0';
    printf("\n=== Reconstruction infixe (TP3) ===\n  \"%s\"\n", buf_infixe);
 
    /* Étape 6 : libérer la mémoire */
    delete_binary_tree(&ast);
    printf("\n=== Memoire liberee. Fin. ===\n");
    return 0;
}