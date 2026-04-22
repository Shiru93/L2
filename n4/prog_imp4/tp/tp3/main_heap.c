/*
 * main_heap.c  —  TP3, Exercice 2 : Tri par tas
 *
 * Le programme :
 *   1. Lit n en argument de la ligne de commande.
 *   2. Alloue et initialise aléatoirement t[0..n-1] (valeurs 0–99).
 *   3. Affiche t entier, puis le segment t[lo..hi] où lo = n/3, hi = n - n/3 - 1.
 *   4. Trie t[lo..hi] par heap_sort.
 *   5. Affiche t entier (les éléments hors segment sont inchangés),
 *      puis le segment trié.
 *   6. Libère la mémoire.
 *
 * -----------------------------------------------------------------------
 * RAPPEL : stockage d'un tas dans un tableau
 *
 * Un tas est un arbre binaire quasi-complet stocké SANS pointeurs :
 * on utilise les formules d'indexation suivantes pour un segment t[lo..hi]
 * (lo est la "racine" logique) :
 *
 *   indice de la racine : lo
 *   fils gauche de t[i] : 2*(i - lo) + 1 + lo  =  2*i - lo + 1
 *   fils droit  de t[i] : 2*(i - lo) + 2 + lo  =  2*i - lo + 2
 *   parent de t[i]      : (i - lo - 1)/2 + lo
 *
 * Propriété du tas-MAX : t[parent] >= t[fils]
 * → la RACINE contient toujours le plus grand élément.
 *
 * -----------------------------------------------------------------------
 * fixHeap(t, lo, hi, i)
 *
 *   Suppose que les sous-arbres gauche et droit de t[i] sont déjà
 *   des tas-max. Fait "descendre" t[i] jusqu'à ce que la propriété
 *   de tas soit restaurée au niveau de t[i] aussi.
 *
 *   Algorithme :
 *     Tant que t[i] a au moins un fils dans [lo..hi] :
 *       j = indice du plus grand fils
 *       si t[i] >= t[j] : déjà en ordre → stop
 *       sinon : échanger t[i] et t[j], continuer à descendre depuis j
 *
 * -----------------------------------------------------------------------
 * buildHeap(t, lo, hi)
 *
 *   Transforme le segment t[lo..hi] en tas-max.
 *   Seuls les nœuds internes (non-feuilles) ont besoin d'être traités.
 *   Le dernier nœud interne a l'indice : lo + (hi - lo - 1) / 2
 *   On appelle fixHeap en partant de ce dernier nœud interne vers lo.
 *
 * -----------------------------------------------------------------------
 * heap_sort(t, lo, hi)
 *
 *   Phase 1 : buildHeap → t[lo] contient le max.
 *   Phase 2 : n-1 fois :
 *     - échanger t[lo] (max actuel) avec t[hi] (dernière place libre)
 *     - réduire hi d'un cran
 *     - fixHeap depuis lo pour restaurer le tas
 *   → après n-1 échanges, le tableau est trié par ordre croissant.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "fonctions.h"

int main(int argc, char * argv[]){
    /* ---- Étape 1 : lire n depuis la ligne de commande ---- */
    if(argc != 2){
        fprintf(stderr, "Erreur : n doit être un entier strictement positif.\n");
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    if(n <= 0){
        fprintf(stderr, "Erreur : n doit être un entier strictement positif.\n");
        return EXIT_FAILURE;
    }

    int * t = malloc(n * sizeof(int));
    if(!t){
        fprintf(stderr, "Erreur : allocation mémoire impossinle");
        return EXIT_FAILURE;
    }

    /* ---- Étape 2 : initialisation pseudo-aléatoire ---- */
    srand((unsigned int)time(NULL));
    for(int i = 0; i < n; i++){
        t[i] = rand() % 100; // Valeur entre 0 et 99
    }

    /* Calcul des bornes du segment : lo = floor(n/3), hi = n - floor(n/3) - 1 */
    int lo = n / 3;
    int hi = n - n / 3 - 1;

    printf("=== Tableau initial (n = %d) ===\n  ", n);
    print_array(t, n);
 
    printf("\n=== Segment t[%d..%d] avant tri ===\n  ", lo, hi);
    print_segment(t, lo, hi);

    /* ---- Étape 3 : trier le segment ---- */
    heap_sort(t, lo, hi);

    printf("\n=== Tableau après tri du segment ===\n  ");
    print_array(t, n);
 
    printf("\n=== Segment t[%d..%d] après tri ===\n  ", lo, hi);
    print_segment(t, lo, hi);
 
    /* ---- Étape 4 : libérer la mémoire ---- */
    free(t);
    printf("\n=== Mémoire libérée. Fin. ===\n");
 
    return EXIT_SUCCESS;
}