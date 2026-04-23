/*
 * bst.c — TP4 : fonctions ABR à compléter
 *
 * Ce fichier contient les 4 fonctions demandées.
 * Les fonctions déjà fournies (insert_BST, insert_BST_it,
 * insert_BST_root, select_BST, rotate_left, rotate_right)
 * sont dans bst_cm5_2026.c.
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
 
/* ================================================================== */
/*  insert_BST_root_it                                                 */
/* ================================================================== */
/*
 * Insère la valeur v À LA RACINE d'un ABR, de façon ITÉRATIVE.
 *
 * IDÉE CENTRALE — "split puis recolle" :
 *
 *   On crée un nouveau nœud racine contenant v.
 *   On parcourt l'arbre original et on répartit TOUS ses nœuds
 *   soit dans le sous-arbre gauche de v (nœuds < v),
 *   soit dans le sous-arbre droit de v (nœuds >= v).
 *
 *   Pour ça, on maintient deux "queues d'attente" :
 *     - left_ptr  : pointeur vers l'endroit où accrocher le prochain
 *                   nœud qui part à gauche
 *     - right_ptr : idem à droite
 *
 *   À chaque étape :
 *     - si cur->label >= v : cur doit être à DROITE de v.
 *       On l'accroche via *right_ptr, et on avance right_ptr vers
 *       cur->left (son futur fils gauche sera le prochain nœud < v).
 *     - si cur->label < v  : cur doit être à GAUCHE de v.
 *       On l'accroche via *left_ptr, et on avance left_ptr vers
 *       cur->right.
 *
 *   À la fin, on bouche les deux extrémités avec NULL.
 *
 * EXEMPLE : ABR = {3, 5, 7}, on insère 4 à la racine.
 *
 *   Arbre initial :     5
 *                      / \
 *                     3   7
 *
 *   nouveau nœud v=4, left_ptr→(v->left), right_ptr→(v->right)
 *
 *   cur = nœud(5) : 5 >= 4 → *right_ptr = nœud(5)
 *                             right_ptr → nœud(5)->left
 *                             cur = nœud(5)->left = nœud(3)
 *
 *   cur = nœud(3) : 3 < 4  → *left_ptr = nœud(3)
 *                             left_ptr → nœud(3)->right
 *                             cur = nœud(3)->right = NULL
 *
 *   Fin : *left_ptr = NULL → nœud(3)->right = NULL
 *         *right_ptr = NULL → nœud(5)->left = NULL
 *
 *   Résultat :    4
 *               /   \
 *              3     5
 *                     \
 *                      7     ← identique à la version récursive ✓
 *
 * Complexité : O(h) où h est la hauteur de l'arbre.
 */
link insert_BST_root_it(link h, item v){
    // Créer le nouveau noeud racine
    link new_node = cons_binary_tree(v, NULL, NULL);
    if(h == NULL)
        return new_node;

    /*
     * left_ptr et right_ptr sont des pointeurs vers des pointeurs.
     * Ils indiquent OÙ écrire le prochain nœud qui sera rattaché
     * à gauche (resp. à droite) du nouveau nœud v.
     */
    link * left_ptr = &(new_node->left);
    link * right_ptr = &(new_node->right);

    link cur = h;
    while(cur != NULL){
        if(less(v, get_binary_tree_root(cur))){
            /*
             * cur->label >= v  : cur va dans le sous-arbre DROIT de v.
             * On l'accroche à la position pointée par right_ptr.
             * Le prochain nœud droit sera attaché à cur->left
             * (car les nœuds < v dans le sous-arbre de cur
             *  seront plus tard déplacés à gauche de v).
             */
            *right_ptr = cur;
            right_ptr = &(cur->left);
            cur = cur->left;
        } else {
            // cur->label < v : cur va dans le sous-arbre gauche de v
            *left_ptr = cur;
            left_ptr = &(cur->right);
            cur = cur->right;
        }
    }

    // Boucher les extrémités des deux chaînes
    *left_ptr = NULL;
    *right_ptr = NULL;

    return new_node;
}

/* ================================================================== */
/*  partition_BST                                                      */
/* ================================================================== */
/*
 * Amène le nœud de rang k (0-indexé) à la RACINE de l'ABR,
 * en préservant la propriété d'ABR.
 *
 * RAPPEL : le rang d'un nœud = nombre de nœuds strictement plus petits.
 *   rang 0 = le plus petit, rang n-1 = le plus grand.
 *
 * ALGORITHME (récursif) :
 *   Soit t = taille du sous-arbre gauche de h (= rang de h->label).
 *
 *   Cas 1 : t == k  → h est déjà le k-ème nœud, on retourne h.
 *
 *   Cas 2 : t > k   → le k-ème nœud est dans le sous-arbre GAUCHE.
 *     On amène récursivement le rang k à la racine du sous-arbre gauche,
 *     puis on fait une rotation DROITE pour le faire monter.
 *
 *   Cas 3 : t < k   → le k-ème nœud est dans le sous-arbre DROIT.
 *     Son rang dans ce sous-arbre est k - t - 1 (on retire t nœuds
 *     gauches + 1 pour la racine).
 *     On amène récursivement ce rang à la racine du sous-arbre droit,
 *     puis on fait une rotation GAUCHE.
 *
 * EXEMPLE : ABR = {1,3,5,7,9}, k=2 (on veut amener '5' à la racine)
 *
 *       5(rang=2)
 *      / \
 *     3   7
 *    /   / \
 *   1   6   9     ← exemple plus riche
 *
 *   t = size(gauche) = 2, k = 2 → t == k → retourne h directement.
 *
 * Complexité : O(n) dans le pire cas (taille calculée à chaque appel).
 */
link partition_BST(link h, int k){
    if(h == NULL)
        return NULL;

    // t = rang du noeud racine = nombre de noeuds dans son sous-arbre gauche
    int t = size_binary_tree(h->left);

    if(t > k){
        /*
         * Le k-ème est dans le sous-arbre gauche.
         * On l'amène à la racine du sous-arbre gauche,
         * puis rotate_right le fait monter d'un niveau.
         */
        h->left = partition_BST(h->left, k);
        h = rotate_right(h);
    } else if (t < k){
        /*
         * Le k-ème est dans le sous-arbre droit.
         * Son rang local dans le sous-arbre droit = k - t - 1
         * (on enlève t nœuds gauches + 1 pour la racine courante).
         */
        h->right = partition_BST(h->right, k - t - 1);
        h = rotate_left(h);
    }

    // Si t == k : la racine est déjà le k-ème noeud, rien à faire
    
    return h;
}

/* ================================================================== */
/*  join_BST  (fonction locale, non déclarée dans bst.h)              */
/* ================================================================== */
/*
 * Fusionne deux ABR L et R où TOUS les éléments de L < TOUS les
 * éléments de R.
 *
 * IDÉE :
 *   - Si L ou R est vide → trivial.
 *   - On amène le plus PETIT élément de R à la racine de R
 *     via partition_BST(R, 0).
 *     → ce plus petit élément n'a pas de fils gauche (c'est le min).
 *   - On attache L comme fils gauche de cette nouvelle racine.
 *
 * Utilisée par delete_node_BST pour reconstituer l'arbre après
 * suppression d'un nœud.
 */
link join_BST(link L, link R){
    if(L == NULL) return R;
    if(R == NULL) return L;

    // Amener le minimum de R à la racine
    R = partition_BST(R, 0);

    // R->left est forcément NULL (c'était le minimum)
    R->left = L;

    return R;
}

/* ================================================================== */
/*  delete_node_BST                                                    */
/* ================================================================== */
/*
 * Supprime le nœud contenant la valeur v dans l'ABR h.
 *
 * ALGORITHME (récursif) :
 *
 *   1. Si h est vide → rien à supprimer, retourne NULL.
 *
 *   2. Comparer v avec la racine :
 *      - v < racine → supprimer dans le sous-arbre gauche.
 *      - v > racine → supprimer dans le sous-arbre droit.
 *      - v == racine → c'est ce nœud qu'on supprime.
 *
 *   3. Pour supprimer la racine :
 *      On récupère ses deux sous-arbres L (gauche) et R (droit).
 *      On les fusionne avec join_BST(L, R) qui donne un ABR valide
 *      contenant tous les nœuds sauf v.
 *      On libère le nœud supprimé avec free().
 *
 * EXEMPLE : supprimer '5' dans {3,5,7,9}
 *
 *     5          → on supprime la racine
 *    / \
 *   3   7            L = {3},  R = {7,9}
 *        \
 *         9
 *                 join_BST({3}, {7,9}) :
 *                   partition_BST({7,9}, 0) → amène 7 à la racine
 *                   7->left = {3}
 *                   résultat :   7
 *                               / \
 *                              3   9   ✓ ABR valide
 *
 * Complexité : O(n) dans le pire cas.
 */
link delete_node_BST(link h, item v){
    if(h == NULL)
        return NULL;

    item racine = get_binary_tree_root(h);

    if(eq(v, racine)){
        // Supprimer la racine : fusionner les deux sous-arbres
        link L = h->left;
        link R = h->right;
        
        free(h);

        return join_BST(L, R);
    } else if(less(v, racine)){
        h->left = delete_node_BST(h->left, v);
    } else {
        h->right = delete_node_BST(h->right, v);
    }

    return h;
}

/* ================================================================== */
/*  balance_BST                                                        */
/* ================================================================== */
/*
 * Rééquilibre un ABR pour le rendre aussi "plat" que possible.
 *
 * ALGORITHME (récursif, diviser pour régner) :
 *
 *   1. Si l'arbre a 0 ou 1 nœud → déjà équilibré, retourner h.
 *
 *   2. Calculer l'indice du médian : m = n / 2  (division entière)
 *      Amener le médian à la racine via partition_BST(h, m).
 *      → le médian sépare l'arbre en deux moitiés approximativement
 *        égales : ~ m nœuds à gauche, ~ n-m-1 nœuds à droite.
 *
 *   3. Rééquilibrer récursivement le sous-arbre gauche.
 *   4. Rééquilibrer récursivement le sous-arbre droit.
 *
 * EXEMPLE : {1,2,3,4,5} → médian = rang 2 = valeur '3'
 *
 *   Avant (dégénéré) :    1          Après balance :    3
 *                          \                           / \
 *                           2                         1   4
 *                            \                         \   \
 *                             3                         2   5
 *                              \
 *                               4
 *                                \
 *                                 5
 *
 * La hauteur passe de 4 à 2 → beaucoup plus efficace pour la recherche.
 *
 * Complexité : O(n²) dans le pire cas (size_binary_tree est O(n)
 * et partition_BST est O(n), appelés O(n) fois au total).
 */
link balance_BST(link h){
    int n = size_binary_tree(h);
    if(n <= 1) return h;

    // Amener le médian à la racine
    int m = n / 2;
    h = partition_BST(h, m);

    // Rééquilibrer récursivement les deux sous-arbres
    h->left = balance_BST(h->left);
    h->right = balance_BST(h->right);

    return h;
}

/* ------------------------------------------------------------------ */
/*  Utilitaires                                                        */
/* ------------------------------------------------------------------ */
 
/* Compare deux arbres nœud par nœud (même structure ET mêmes labels) */
int same_tree(link a, link b){
    if(a == NULL && b == NULL)
        return 1;

    if(a == NULL || b == NULL)
        return 0;

    return eq(a->label, b->label) && same_tree(a->left, b->left) && same_tree(a->right, b->right);
}