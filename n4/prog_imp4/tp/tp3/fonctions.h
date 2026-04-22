#ifndef FONCTIONS_H
#define FONCTIONS_H

/* Échange deux entiers */
void swap(int *a, int *b);

/* Affiche le tableau entier */
void print_array(const int *t, int n);

/* Affiche le segment t[lo..hi] inclus */
void print_segment(const int *t, int lo, int hi);

void fixHeap(int *t, int lo, int hi, int i);
void buildHeap(int *t, int lo, int hi);
void heap_sort(int *t, int lo, int hi);

#endif