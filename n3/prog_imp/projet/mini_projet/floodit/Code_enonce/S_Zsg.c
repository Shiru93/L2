#include "S_Zsg.h"

/* * Fonction : free_Zsg
 * Rôle : Libère proprement toute la mémoire allouée dynamiquement pour la structure S_Zsg.
 * Ordre : D'abord les contenus (listes), puis les conteneurs (tableaux).
 */
void free_Zsg(S_Zsg * Z){
    // 1. Libération de la liste des cases de la zone inondée
    detruit_liste(&(Z->Lzsg));
    
    // 2. Libération du tableau de listes de bordures
    if(Z->B){
        for(int i = 0; i < Z->nbcl; i++){
            detruit_liste(&(Z->B[i]));
        }
        free(Z->B);
    }

    // 3. Libération de la matrice d'appartenance (App)
    if(Z->App){
        for(int i = 0; i < Z->dim; i++){
            if(Z->App[i]){
                free(Z->App[i]);
            }
        }
        free(Z->App);
    }
}

/* --- Exercice 2.1 --- */
/* * Fonction : init_Zsg
 * Rôle : Initialise la structure (dimensions, allocation mémoire).
 * La matrice App est remplie de -2 (code pour "case non visitée").
 */
int init_Zsg(S_Zsg * L, int dim, int nbcl){
    L->dim = dim;
    L->nbcl = nbcl;

    init_liste(&(L->Lzsg));

    // Allocation du tableau de listes pour les bordures (une liste par couleur)
    L->B = malloc(sizeof(ListeCase) * nbcl);
    for(int i = 0; i < nbcl; i++)
        init_liste(&(L->B[i]));

    // Allocation de la matrice App
    L->App = malloc(sizeof(int *) * dim);
    if(!L->App)
        return 1;

    for (int i = 0; i < dim; i++){
        L->App[i] = malloc(sizeof(int) * dim);
        for(int j = 0; j < dim; j++)
            L->App[i][j] = -2; // -2 signifie "Inconnu / Hors zone / Hors bordure"
    }

    return 0;
}

/* Ajoute une case à la zone Zsg et met à jour App à -1 */
void ajoute_Zsg(S_Zsg * L, int i, int j){
    ajoute_en_tete(&(L->Lzsg), i, j);
    L->App[i][j] = -1;
}

/* Ajoute une case à la bordure d'une couleur donnée et met à jour App */
void ajoute_Bordure(S_Zsg * L, int i, int j, int nbcl){
    ajoute_en_tete(&(L->B[nbcl]), i, j);
    L->App[i][j] = nbcl; // On stocke la couleur dans App pour identifier la bordure
}

/* Vérifie si une case est dans la Zsg en O(1) grâce à App */
int appartient_Zsg(S_Zsg * L, int i, int j){
    return (L->App[i][j] == -1);
}

/* Vérifie si une case est dans une bordure spécifique en O(1) */
int appartient_Bordure(S_Zsg * L, int i, int j, int cl){
    return (L->App[i][j] == cl);
}


/* --- Exercice 2.2 --- */
/* * Fonction : agrandit_Zsg
 * Rôle : Cœur de l'optimisation. Étend la zone Zsg à partir d'un point (k,l).
 * Met à jour les frontières (B) au fur et à mesure de l'exploration.
 * Retourne : Le nombre de nouvelles cases ajoutées à la zone.
 */
int agrandit_Zsg(int ** M, S_Zsg * Z, int cl, int k, int l){
    int 
        i, j, 
        nb = 0, 
        x1[] = {0, 0, 1, -1}, 
        y1[] = {1, -1, 0, 0}, 
        x2, y2, 
        nv_couleur;

    ListeCase Pile = NULL;
    
    // Initialisation de la pile avec la case de départ (souvent une case de bordure)
    ajoute_en_tete(&Pile, k, l);


    while(!test_liste_vide(&Pile)){
        enleve_en_tete(&Pile, &i, &j);

        // Si déjà traité, on ignore
        if(Z->App[i][j] == -1)
            continue;

        // Marquage de la case comme conquise
        ajoute_en_tete(&(Z->Lzsg), i, j);
        Z->App[i][j] = -1;

        nb++;

        // Exploration des 4 voisins
        for(int a = 0; a < 4; a++){
            x2 = i + x1[a];
            y2 = j + y1[a];

            // Vérification des limites de la grille
            if(x2 >= 0 && x2 < Z->dim && y2 >= 0 && y2 < Z->dim){
                
                // Si le voisin est déjà dans la Zsg, on passe
                if(Z->App[x2][y2] == -1)
                    continue;

                // Cas 1 : Le voisin est de la MÊME COULEUR -> Propagation
                if(M[x2][y2] == cl){
                    if(Z->App[x2][y2] != -1) // Si pas déjà dans Zsg
                        ajoute_en_tete(&Pile, x2, y2);
                } 
                // Cas 2 : Le voisin est d'une AUTRE COULEUR -> Devient une Bordure
                else {
                    nv_couleur = M[x2][y2];

                    // On l'ajoute à la bordure correspondante s'il n'y est pas déjà
                    if(Z->App[x2][y2] != nv_couleur){
                        ajoute_en_tete(&(Z->B[nv_couleur]), x2, y2);
                        Z->App[x2][y2] = nv_couleur;
                    }
                }
            }
        }
    }

    return nb;
}

/* --- Exercice 2.3 --- */
/* * Fonction : sequence_aleatoire_rapide
 * Rôle : Joue une partie complète en choisissant les couleurs au hasard.
 * Optimisation : Ne traite que les listes de bordures, pas toute la grille.
 */
int sequence_aleatoire_rapide(int ** M, Grille * G, int dim, int nbcl, int aff){
    S_Zsg Z;

    int 
        taille = 0,
        chgmt_couleur = 0,
        ancienne_couleur = M[0][0],
        cl;

    ListeCase L, bordure, tmp;

    // Initialisation
    if(init_Zsg(&Z, dim, nbcl) != 0)
        return -1;

    // Premier appel pour construire la zone initiale depuis (0,0)
    taille += agrandit_Zsg(M, &Z, ancienne_couleur, 0, 0);

    while(taille < dim * dim){
        chgmt_couleur++;

        // Choix aléatoire d'une couleur valide (non vide et différente de l'actuelle)
        do{
            cl = rand() % nbcl;
        } while(cl == ancienne_couleur || test_liste_vide(&(Z.B[cl])));

        ancienne_couleur = cl;

        // Mise à jour visuelle (optionnelle si aff=0)
        L = Z.Lzsg;
        while(L){
            M[L->i][L->j] = ancienne_couleur;
            if(aff){
                Grille_attribue_couleur_case(G, L->i, L->j, ancienne_couleur);
                // Grille_redessine_Grille(G);
                // usleep(10000);

                // Grille_attente_touche();
            }
                

            L = L->suiv;
        }

        if(aff){
            Grille_redessine_Grille(G);
            Grille_attente_touche();
        }

        // --- POINT CLÉ ---
        // On récupère la liste de bordure de la couleur choisie
        bordure = Z.B[ancienne_couleur];
        Z.B[ancienne_couleur] = NULL; // On vide la liste dans la structure

        // On appelle agrandit_Zsg pour chaque point de cette bordure
        while(bordure){
            taille += agrandit_Zsg(M, &Z, ancienne_couleur, bordure->i, bordure->j);
            tmp = bordure;
            bordure = bordure->suiv;
            free(tmp); // On libère le maillon de la liste de bordure traité
        }
    }

    free_Zsg(&Z);

    return chgmt_couleur;
}

/* --- Exercice 3.1 --- */
/* Compte le nombre d'éléments dans la liste de bordure d'une couleur donnée */
int nombre_couleur(S_Zsg * Z, int cl){
    int nb = 0;
    ListeCase courant = Z->B[cl];

    while(courant){
        nb++;
        courant = courant->suiv;
    }
    
    return nb;
}

/* --- Exercice 3.2 --- */
/* * Fonction : strategie_max_bordure
 * Rôle : Choisit la couleur qui augmente le plus la taille de la Zsg (vision à court terme).
 */
int strategie_max_bordure(int ** M, Grille * G, int dim, int nbcl, int aff){
    S_Zsg Z;

    int 
        max_couleur,
        tmp,
        chgmt_couleur = 0,
        taille = 0,
        max_taille,
        ancienne_couleur = M[0][0],
        cl;

    ListeCase
        L,
        bordure,
        tmp_liste;

    if(init_Zsg(&Z, dim, nbcl) != 0)
        return -1;

    taille += agrandit_Zsg(M, &Z, ancienne_couleur, 0, 0);

    while(taille < dim * dim){
        chgmt_couleur++;

        max_taille = -1;
        max_couleur = -1;
        
        // Recherche de la meilleure couleur
        for(int i = 0; i < nbcl; i++){
            if(i == ancienne_couleur)
                continue;

            tmp = nombre_couleur(&Z, i); // Appel Exo 3.1

            if(tmp > max_taille){
                max_taille = tmp;
                max_couleur = i;
            }
        }

        if(max_couleur == -1)
            continue;

        cl = max_couleur;

        ancienne_couleur = cl;

        // Application du changement de couleur
        L = Z.Lzsg;
        while(L){
            M[L->i][L->j] = cl;
            if(aff) {
                Grille_attribue_couleur_case(G, L->i, L->j, cl);
                // Grille_redessine_Grille(G);
                // usleep(10000);

                // Grille_attente_touche();
            }
            L = L->suiv;
        }

        if(aff){
            Grille_redessine_Grille(G);
            Grille_attente_touche();
        }

        // Propagation
        bordure = Z.B[cl];
        Z.B[cl] = NULL;

        while(bordure){
            taille += agrandit_Zsg(M, &Z, cl, bordure->i, bordure->j);
            tmp_liste = bordure;
            bordure = bordure->suiv;
            free(tmp_liste);
        }
    }

    free_Zsg(&Z);

    return chgmt_couleur;
}

/* --- Exercice 4.1 --- */
/* * Fonction : fonction_annexe (Simulation)
 * Rôle : Simule une expansion (BFS) sans modifier la vraie structure Zsg.
 * Utilise une matrice 'visite' locale pour ne pas compter deux fois les mêmes cases.
 */
int fonction_annexe(int ** M, int dim, ListeCase bordure, int cl, int ** App){
    int 
        nb_nvl_cases = 0,
        ** visite = malloc(sizeof(int *) * dim),
        i, j,
        x, y,
        xtab[] = {0, 0, 1, -1},
        ytab[] = {1, -1, 0, 0};

    ListeCase 
        Pile = NULL,
        b = bordure;

    // Initialisation de la matrice visite à 0
    for(int k = 0; k < dim; k++)
        visite[k] = calloc(dim, sizeof(int));

    // Copie de la bordure dans la pile de traitement
    while(b){
        ajoute_en_tete(&Pile, b->i, b->j);
        b = b->suiv;
    }

    // Parcours simulé
    while(!test_liste_vide(&Pile)){
        enleve_en_tete(&Pile, &i, &j);

        // Si déjà visité dans la simu OU déjà dans la vraie Zsg, on ignore
        if(visite[i][j] == 1 || App[i][j] == -1)
            continue;
        
        visite[i][j] = 1;
        nb_nvl_cases++;

        for(int v = 0; v < 4; v++){
            x = i + xtab[v];
            y = j + ytab[v];

            if(x >= 0 && x < dim && y >= 0 && y < dim){
                // On propage si c'est la bonne couleur et pas encore visité
                if(M[x][y] == cl && App[x][y] != -1 && visite[x][y] == 0){
                    ajoute_en_tete(&Pile, x, y);
                }
            }
        }
    }

    // Nettoyage de la mémoire temporaire
    for(int i = 0; i < dim; i++)
        free(visite[i]);

    free(visite);

    return nb_nvl_cases; // Retourne le gain réel potentiel
}

/* * Fonction : strategie_max_bordure_zone (Exo 4)
 * Rôle : Stratégie intelligente qui simule les coups pour maximiser le gain total (bordure + zone derrière).
 */
int strategie_max_bordure_zone(int ** M, Grille * G, int dim, int nbcl, int aff){
    S_Zsg Z;

    int 
        taille = 0,
        chgmt_couleur = 0,
        ancienne_couleur = M[0][0],
        max_couleur,
        max_gain,
        simule_gain;

    ListeCase 
        L,
        bordure,
        tmp;

    if(init_Zsg(&Z, dim, nbcl) != 0)
        return -1;

    taille += agrandit_Zsg(M, &Z, ancienne_couleur, 0, 0);

    while(taille < dim * dim){
        chgmt_couleur++;

        max_couleur = -1;
        max_gain = -1;

        // On teste toutes les couleurs possibles
        for(int c = 0; c < nbcl; c++){
            if(c == ancienne_couleur)
                continue;

            if(test_liste_vide(&(Z.B[c])))
                continue;

            // On simule le gain réel avec la fonction annexe
            simule_gain = fonction_annexe(M, dim, Z.B[c], c, Z.App);

            if(simule_gain > max_gain){
                max_gain = simule_gain;
                max_couleur = c;
            }
        }

        if(max_couleur == -1)
            break;

        ancienne_couleur = max_couleur;

        // Mise à jour de la grille réelle
        L = Z.Lzsg;
        while(L){
            M[L->i][L->j]= ancienne_couleur;
            if(aff){
                Grille_attribue_couleur_case(G, L->i, L->j, ancienne_couleur);
                // Grille_redessine_Grille(G);
                // usleep(10000);

                // Grille_attente_touche();
            } 
            L = L->suiv;
        }

        if(aff) {
            Grille_redessine_Grille(G);
            Grille_attente_touche();
        }

        // Application réelle du coup dans la structure Zsg
        bordure = Z.B[ancienne_couleur];
        Z.B[ancienne_couleur] = NULL;

        while(bordure){
            taille += agrandit_Zsg(M, &Z, ancienne_couleur, bordure->i, bordure->j);
            tmp = bordure;
            bordure = bordure->suiv;
            free(tmp);
        }
    }

    free_Zsg(&Z);

    return chgmt_couleur;
}