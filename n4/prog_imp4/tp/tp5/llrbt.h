#ifndef LLRBT_H
#define LLRBT_H

/*
 * llrbt.h — Left-Leaning Red-Black Tree (LLRBT)
 *
 * Un LLRBT est un ABR équilibré où chaque lien est colorié
 * ROUGE ou NOIR selon les règles suivantes :
 *
 *   1. Propriété ABR : gauche < racine < droite.
 *   2. Un lien rouge penche TOUJOURS à GAUCHE (jamais à droite).
 *   3. Pas deux liens rouges CONSÉCUTIFS sur un chemin.
 *   4. La racine est toujours NOIRE.
 *   5. Tous les chemins racine→feuille ont le même nombre de
 *      liens NOIRS (« hauteur noire » constante).
 *
 * Conséquence : la hauteur totale est au plus 2 * log2(n),
 * ce qui garantit des opérations en O(log n).
 *
 * Le type item est ici int (valeurs entre 0 et 99).
 * La priorité va au plus GRAND entier : less(A,B) = A < B,
 * donc le parcours infixe donne les valeurs en ordre CROISSANT.
 */

#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------------------------ */
/*  Type item = int                                                    */
/* ------------------------------------------------------------------ */
typedef int item;

#define less(A, B)  ((A) < (B))
#define eq(A, B)    ((A) == (B))

/* ------------------------------------------------------------------ */
/*  Couleurs des liens                                                 */
/* ------------------------------------------------------------------ */
#define RED   1
#define BLACK 0

/* ------------------------------------------------------------------ */
/*  Structure d'un nœud LLRBT                                         */
/* ------------------------------------------------------------------ */
/*
 * On ne peut pas réutiliser BT.h car la structure binary_tree
 * n'a pas de champ couleur. On définit ici notre propre nœud.
 *
 * color = couleur du lien ENTRANT dans ce nœud
 *         (convention Sedgewick : la couleur est stockée dans le fils)
 */
typedef struct llrbt_node {
    item              label;  /* valeur stockée             */
    int               color;  /* RED ou BLACK               */
    struct llrbt_node *left;  /* fils gauche (NULL si aucun)*/
    struct llrbt_node *right; /* fils droit  (NULL si aucun)*/
} *llrbt_link;

/* ------------------------------------------------------------------ */
/*  Prototypes                                                         */
/* ------------------------------------------------------------------ */

/* Alloue un nœud rouge avec la valeur v */
llrbt_link new_llrbt_node(item v);

/* Libère récursivement tout l'arbre */
void delete_llrbt(llrbt_link *h);

/* Teste si un nœud est lié par un lien rouge */
int isRed(llrbt_link h);

/* Rotation gauche : corrige un lien rouge à droite */
llrbt_link rotateLeft(llrbt_link h);

/* Rotation droite : corrige deux liens rouges consécutifs à gauche */
llrbt_link rotateRight(llrbt_link h);

/* Inversion des couleurs : deux fils rouges → les rendre noirs,
   la racine devient rouge */
void flipColors(llrbt_link h);

/* Insère v dans le LLRBT et retourne la nouvelle racine */
llrbt_link insert_LLRBT(llrbt_link h, item v);

/* Parcours infixe : remplit t[*idx], *idx, *idx+1, ...
   en ordre croissant */
void inorder_LLRBT(llrbt_link h, item *t, int *idx);

/* Affiche l'arbre tourné de -90° (droite en haut, gauche en bas) */
void show_llrbt(llrbt_link h, int lvl);

#endif
