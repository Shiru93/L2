/*
 * llrbt.c — Implémentation du Left-Leaning Red-Black Tree
 *
 * Algorithme de Robert Sedgewick (2008).
 * Référence : "Left-leaning Red-Black Trees", Sedgewick, 2008.
 */

#include "llrbt.h"

/* ================================================================== */
/*  new_llrbt_node                                                     */
/* ================================================================== */
/*
 * Alloue et initialise un nouveau nœud.
 * Tout nouveau nœud est ROUGE : il représente un lien rouge entrant,
 * ce qui correspond à l'ajout d'une clé dans un nœud 2-3 existant.
 */
llrbt_link new_llrbt_node(item v) {
    llrbt_link h = malloc(sizeof(struct llrbt_node));
    if (!h) { fprintf(stderr, "Erreur malloc\n"); exit(1); }
    h->label = v;
    h->color = RED;    /* tout nouveau nœud est rouge */
    h->left  = NULL;
    h->right = NULL;
    return h;
}

/* ================================================================== */
/*  delete_llrbt                                                       */
/* ================================================================== */
/*
 * Libère récursivement tous les nœuds de l'arbre (parcours postordre).
 * Met *h à NULL après libération pour éviter un pointeur fantôme.
 */
void delete_llrbt(llrbt_link *h) {
    if (!h || *h == NULL) return;
    delete_llrbt(&((*h)->left));
    delete_llrbt(&((*h)->right));
    free(*h);
    *h = NULL;
}

/* ================================================================== */
/*  isRed                                                              */
/* ================================================================== */
/*
 * Retourne 1 si le lien entrant dans h est rouge, 0 sinon.
 * Par convention, NULL est BLACK (les feuilles virtuelles sont noires).
 */
int isRed(llrbt_link h) {
    if (h == NULL) return 0;
    return h->color == RED;
}

/* ================================================================== */
/*  rotateLeft                                                         */
/* ================================================================== */
/*
 * QUAND : le fils DROIT est rouge (violation de la règle "left-leaning").
 *
 * AVANT :          h (couleur C)          APRÈS :      x (couleur C)
 *                 / \                                  / \
 *                A   x (RED)                     h (RED)  B
 *               / \                              / \
 *              B   ...                          A   ...
 *
 * On fait monter x à la place de h :
 *   - x hérite de la couleur de h (pour ne pas changer l'équilibre noir)
 *   - h devient rouge (il est maintenant "enfant gauche" de x)
 *   - le sous-arbre gauche de x (B) devient le sous-arbre droit de h
 *
 * Complexité : O(1)
 */
llrbt_link rotateLeft(llrbt_link h) {
    llrbt_link x = h->right;  /* x = fils droit rouge     */
    h->right = x->left;       /* B devient fils droit de h */
    x->left  = h;             /* h devient fils gauche de x */
    x->color = h->color;      /* x hérite la couleur de h  */
    h->color = RED;           /* h devient rouge            */
    return x;                 /* x est la nouvelle racine  */
}

/* ================================================================== */
/*  rotateRight                                                        */
/* ================================================================== */
/*
 * QUAND : le fils GAUCHE et le fils gauche du fils gauche sont rouges
 *         (deux liens rouges consécutifs à gauche).
 *
 * AVANT :           h (couleur C)         APRÈS :     x (couleur C)
 *                  / \                               / \
 *           (RED) x   B                            A   h (RED)
 *                / \                                   / \
 *          (RED) A  ...                              ...   B
 *
 * Symétrique de rotateLeft.
 *
 * Complexité : O(1)
 */
llrbt_link rotateRight(llrbt_link h) {
    llrbt_link x = h->left;   /* x = fils gauche rouge     */
    h->left  = x->right;      /* sous-arbre droit de x → fils gauche de h */
    x->right = h;             /* h devient fils droit de x */
    x->color = h->color;      /* x hérite la couleur de h  */
    h->color = RED;           /* h devient rouge            */
    return x;
}

/* ================================================================== */
/*  flipColors                                                         */
/* ================================================================== */
/*
 * QUAND : les DEUX fils sont rouges (nœud 4 dans un arbre 2-3-4).
 *
 * On inverse les couleurs de la racine ET de ses deux fils :
 *   - les fils rouges deviennent noirs  (ils "montent" dans leur père)
 *   - la racine noire devient rouge     (elle "remonte" vers son père)
 *
 * AVANT :        h (BLACK)       APRÈS :      h (RED)
 *               / \                           / \
 *        (RED) x   y (RED)            (BLACK) x   y (BLACK)
 *
 * Cela correspond à la "division" d'un nœud 4 dans un arbre 2-3.
 *
 * Complexité : O(1)
 */
void flipColors(llrbt_link h) {
    h->color        = !(h->color);
    h->left->color  = !(h->left->color);
    h->right->color = !(h->right->color);
}

/* ================================================================== */
/*  insert_LLRBT                                                       */
/* ================================================================== */
/*
 * Insère la valeur v dans le LLRBT et retourne la nouvelle racine.
 *
 * ALGORITHME (récursif) :
 *
 *   Étape 1 — Descente BST standard :
 *     Si v < racine → descendre à gauche
 *     Si v > racine → descendre à droite
 *     Si v == racine → mettre à jour (on ne crée pas de doublon)
 *
 *   Étape 2 — Remontée : appliquer les 3 corrections dans l'ordre
 *     en remontant la récursion :
 *
 *     Correction 1 — rotateLeft :
 *       Si fils DROIT rouge et fils GAUCHE noir
 *       → le lien rouge est à droite, violation "left-leaning"
 *       → on le fait basculer à gauche par rotation gauche
 *
 *     Correction 2 — rotateRight :
 *       Si fils GAUCHE rouge ET petit-fils GAUCHE rouge
 *       → deux rouges consécutifs à gauche
 *       → rotation droite pour rééquilibrer
 *
 *     Correction 3 — flipColors :
 *       Si fils GAUCHE rouge ET fils DROIT rouge
 *       → nœud 4 temporaire → on éclate en faisant monter la racine
 *
 * IMPORTANT : après toutes les corrections, on force la racine à être
 * NOIRE (règle 4 du LLRBT).
 *
 * EXEMPLE d'insertion de 5 dans {3, 7, 9} :
 *
 *   Arbre :    7(B)              5 < 7 → aller à gauche
 *             / \               5 > 3 → aller à droite de 3
 *           3(B) 9(B)           → on crée nœud(5, RED)
 *
 *   Remontée depuis 3 :
 *     fils droit(5) rouge, fils gauche NULL(noir) → rotateLeft(3)
 *     Résultat :   5(RED)
 *                 / \
 *               3(B) NULL
 *
 *   Remontée depuis 7 :
 *     maintenant h->left = 5(RED), h->left->left = 3(RED)
 *     → deux rouges consécutifs → rotateRight(7)
 *     Résultat :   5(ancienne couleur de 7 = B)
 *                 / \
 *              3(RED) 7(RED)
 *                       \
 *                       9(B)
 *     deux fils rouges → flipColors
 *     Résultat :   5(RED)
 *                 / \
 *              3(B) 7(B)
 *                     \
 *                     9(B)
 *
 *   Racine forcée à BLACK en fin d'appel top-level.
 */
llrbt_link insert_LLRBT(llrbt_link h, item v) {
    /* Cas de base : arbre vide → nouveau nœud rouge */
    if (h == NULL) return new_llrbt_node(v);

    /* Étape 1 : descente BST
     * Pour les doublons (v == racine), on insère à droite pour
     * conserver une taille n exacte comme demandé par l'énoncé.
     * "Priorité au plus grand" = les égaux vont à droite. */
    if (less(v, h->label)) h->left  = insert_LLRBT(h->left,  v);
    else                   h->right = insert_LLRBT(h->right, v);

    /* Étape 2 : corrections en remontant */

    /* Correction 1 : lien rouge à droite → rotation gauche */
    if (isRed(h->right) && !isRed(h->left))
        h = rotateLeft(h);

    /* Correction 2 : deux rouges consécutifs à gauche → rotation droite */
    if (isRed(h->left) && isRed(h->left->left))
        h = rotateRight(h);

    /* Correction 3 : deux fils rouges → flipColors */
    if (isRed(h->left) && isRed(h->right))
        flipColors(h);

    return h;
}

/* ================================================================== */
/*  inorder_LLRBT                                                      */
/* ================================================================== */
/*
 * Parcourt le LLRBT en ordre INFIXE (gauche → racine → droite)
 * et remplit le tableau t à partir de l'indice *idx.
 *
 * Comme la propriété ABR est respectée, les valeurs sont visitées
 * en ordre CROISSANT → le tableau t est trié après l'appel.
 *
 * Paramètres :
 *   h   — racine du sous-arbre courant
 *   t   — tableau de sortie
 *   idx — pointeur sur l'indice courant d'écriture dans t
 *
 * Complexité : O(n)
 */
void inorder_LLRBT(llrbt_link h, item *t, int *idx) {
    if (h == NULL) return;
    inorder_LLRBT(h->left,  t, idx);  /* visiter gauche */
    t[(*idx)++] = h->label;           /* écrire la racine */
    inorder_LLRBT(h->right, t, idx);  /* visiter droite */
}

/* ================================================================== */
/*  show_llrbt                                                         */
/* ================================================================== */
/*
 * Affiche l'arbre tourné de -90° (le sous-arbre droit est en haut,
 * le sous-arbre gauche en bas). Même convention que show_binary_tree.
 * 'R' = lien rouge entrant, '.' = lien noir.
 */
void show_llrbt(llrbt_link h, int lvl) {
    if (h == NULL) return;
    show_llrbt(h->right, lvl + 1);
    for (int i = 0; i < lvl; i++) printf("    ");
    printf("%c%d\n", h->color == RED ? 'R' : '.', h->label);
    show_llrbt(h->left,  lvl + 1);
}
