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

int main(){
    char expr[256], reconstructed[256];

    /* ---- Étape 1 : lire et afficher l'expression ---- */
    printf("Entrer une expression arithmétique préfixe\n");
    printf("(ex : + * 3 4 5    ou   / - 8 2 + 1 2)\n");
    fgets(expr, sizeof(expr), stdin);

    /* Supprimer le '\n' final laissé par fgets */
    int len = strlen(expr);
    if(len > 0 && expr[len - 1] == '\n'){
        expr[len - 1] = '\0';
        len--;
    }

    printf("\n=== Expression lue ===\n");
    printf("  \"%s\"\n", expr);

    /* ---- Étape 2 : construire et afficher l'arbre syntaxique ---- */
    int pos = 0;
    link ast = parse_expr(expr, &pos);

    printf("\n=== Arbre syntaxique (vue tournée de -90°) ===\n");
    printf("  (la racine est à gauche, les fils vont vers la droite)\n\n");
    show_binary_tree(ast, 0);

    printf("\n  Taille de l'arbre   : %d nœuds\n", size_binary_tree(ast));
    printf("  Hauteur de l'arbre  : %d\n", height_binary_tree(ast));

    /* ---- Étape 3 : évaluer et afficher le résultat ---- */
    int result = eval_tree(ast);
    printf("\n=== Évaluation ===\n");
    printf("  \"%s\"  =  %d\n", expr, result);

    /* ---- Étape 4 : reconstruire l'expression et vérifier ---- */
    int wpos = 0;
    tree_to_expr(ast, reconstructed, &wpos);
    reconstructed[wpos] = '\0';
 
    printf("\n=== Reconstruction (arbre → expression préfixe) ===\n");
    printf("  Expression reconstruite : \"%s\"\n", reconstructed);
 
    if (strcmp(expr, reconstructed) == 0) {
        printf("  ✓ Identique à l'expression originale.\n");
    } else {
        printf("  ✗ DIFFÉRENTE de l'expression originale !\n");
        printf("    Originale    : \"%s\"\n", expr);
        printf("    Reconstruite : \"%s\"\n", reconstructed);
    }

    /* ---- Étape 5 : libérer la mémoire ---- */
    delete_binary_tree(&ast);
    printf("\n=== Mémoire libérée. Fin du programme. ===\n");
 
    return 0;

}