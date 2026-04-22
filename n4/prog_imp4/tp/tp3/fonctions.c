#include <stdio.h>

#include "fonctions.h"

/* ------------------------------------------------------------------ */
/*  Utilitaires                                                        */
/* ------------------------------------------------------------------ */
 
/* Échange deux entiers */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
 
/* Affiche le tableau entier */
void print_array(const int *t, int n) {
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", t[i]);
    printf("]\n");
}
 
/* Affiche le segment t[lo..hi] inclus */
void print_segment(const int *t, int lo, int hi) {
    printf("[ ");
    for (int i = lo; i <= hi; i++)
        printf("%d ", t[i]);
    printf("]\n");
}

/* ------------------------------------------------------------------ */
/*  fixHeap                                                            */
/* ------------------------------------------------------------------ */
/*
 * Fait descendre t[i] dans le tas t[lo..hi] pour restaurer la
 * propriété de tas-max en supposant que les sous-arbres de i sont
 * déjà des tas valides.
 *
 * Paramètres :
 *   t       — le tableau
 *   lo, hi  — bornes du segment (incluses)
 *   i       — indice du nœud à faire descendre
 */
void fixHeap(int *t, int lo, int hi, int i){
    while(1){
        // Indice du fils gauche de t[i] dans le segment [lo...hi]
        int fg = 2 * (i - lo) + 1 + lo;

        // Si pas de fils gauche : t[i] est une feuille -> stop
        if(fg > hi) break;

        // j : indice du plus grand fils
        int j = fg;
        int fd = fg + 1; // fils droit
        if(fd <= hi && t[fd] > t[fg])
            j = fd;

        // Si t[i] >= son plus grand fils : propriété respectée -> stop
        if (t[i] >= t[j]) break;

        // Sinon : echanger et continuer la descente
        swap(&t[i], &t[j]);
        i = j;
    }
}

/* ------------------------------------------------------------------ */
/*  buildHeap                                                          */
/* ------------------------------------------------------------------ */
/*
 * Transforme t[lo..hi] en tas-max en O(n).
 * On parcourt les nœuds internes de droite à gauche (du dernier
 * parent vers la racine) et on appelle fixHeap sur chacun.
 */
void buildHeap(int *t, int lo, int hi){
    // Indice du dernier noeud interne (parent du dernier élément)
    int dernier_interne = lo + (hi - lo - 1) / 2;

    for(int i = dernier_interne; i >= lo; i--)
        fixHeap(t, lo, hi, i);
}

/* ------------------------------------------------------------------ */
/*  heap_sort                                                          */
/* ------------------------------------------------------------------ */
/*
 * Trie t[lo..hi] en ordre croissant par tri par tas.
 *
 * Phase 1 — buildHeap : t[lo] = maximum du segment.
 * Phase 2 — extraction répétée :
 *   On place le max (t[lo]) à sa position finale (t[hi]),
 *   on réduit la taille du tas (hi--),
 *   on restaure le tas (fixHeap).
 */
void heap_sort(int *t, int lo, int hi){
    if(lo >= hi) return; // Segment vide ou un seul élément

    // Phase 1
    buildHeap(t, lo, hi);

    // Phase 2
    int end = hi;
    while(end > lo){
        // t[lo] = max actuel -> on le place à la fin
        swap(&t[lo], &t[end]);
        end--;

        // Restaurer le tas sur t[lo...end]
        fixHeap(t, lo, end, lo);
    }
}