#ifndef _S_ZSG_H_
#define _S_ZSG_H_

#include <stdio.h>
#include <unistd.h>

#include "Liste_case.h"
#include "API_Grille.h"

typedef struct {
    int dim; // Dimension de la grille
    int nbcl; // Nombre de couleur

    ListeCase Lzsg; // Liste des cases de la zone Zsg
    ListeCase * B; // Tableau de listes de cases de la bordure
    int ** App; // Tableau a double entrée des appartenances
} S_Zsg;

void free_Zsg(S_Zsg * Z);

/* EXERCICE 2.1 */
int init_Zsg(S_Zsg * L, int dim, int nbcl);
void ajoute_Zsg(S_Zsg * L, int i, int j);
void ajoute_Bordure(S_Zsg * L, int i, int j, int nbcl);
int appartient_Zsg(S_Zsg * L, int i, int j);
int appartient_Bordure(S_Zsg * L, int i, int j, int cl);

/* Exercice 2.2 */
int agrandit_Zsg(int ** M, S_Zsg * Z, int cl, int k, int l);

/* Exercice 2.3 */
int sequence_aleatoire_rapide(int ** M, Grille * G, int dim, int nbcl, int aff);

/* Exercice 3.1 */
int nombre_couleur(S_Zsg * Z, int cl);

/* Exercice 3.2 */
int strategie_max_bordure(int ** M, Grille * G, int dim, int nbcl, int aff);

/* Exercice 4.1 */
int fonction_annexe(int ** M, int dim, ListeCase bordure, int cl, int ** App);
int strategie_max_bordure_zone(int ** M, Grille * G, int dim, int nbcl, int aff);

#endif