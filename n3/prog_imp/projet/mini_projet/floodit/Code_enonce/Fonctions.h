#ifndef _FONCTIONS_H_
#define _FONCTIONS_H_

#include <stdio.h>
#include <unistd.h>

#include "Liste_case.h"
#include "API_Grille.h"

void trouver_zone_rec_2(int ** M, int dim, int i, int j, int * taille, ListeCase * L, int couleur);
void trouver_zone_rec(int ** M, int dim, int i, int j, int * taille, ListeCase * L);
int sequence_aleatoire_rec(int ** M, Grille * G, int dim, int nbcl, int aff);

#endif