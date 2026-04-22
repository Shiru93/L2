#include "Fonctions.h"

/* * Fonction récursive auxiliaire (DFS - Parcours en profondeur).
 * Elle explore les voisins pour trouver toute la zone connectée de la même couleur.
 */
void trouver_zone_rec_2(int ** M, int dim, int i, int j, int * taille, ListeCase * L, int couleur){
    // Cas de base 1 : On vérifie si on sort des limites de la grille
    if(i < 0 || i >= dim || j < 0 || j >= dim) return;

    // Cas de base 2 : Si la case n'est pas de la bonne couleur, on s'arrête
    // (Note : si M[i][j] vaut -1, cela signifie qu'on est déjà passé par là, donc on s'arrête aussi)
    if(M[i][j] != couleur) return;

    // Marquage : On met la case à -1 pour dire "visitée" et éviter de tourner en rond
    M[i][j] = -1;

    // On ajoute cette case à la liste de la zone (Zsg)
    ajoute_en_tete(L, i, j);
    
    // On incrémente le compteur de taille de la zone
    (*taille)++;

    // Appels récursifs sur les 4 voisins (Bas, Haut, Droite, Gauche)
    trouver_zone_rec_2(M, dim, i + 1, j, taille, L, couleur);
    trouver_zone_rec_2(M, dim, i - 1, j, taille, L, couleur);
    trouver_zone_rec_2(M, dim, i, j + 1, taille, L, couleur);
    trouver_zone_rec_2(M, dim, i, j - 1, taille, L, couleur);
}

/* * Fonction principale de recherche de zone (Wrapper).
 * Elle initialise la recherche et restaure la grille après le marquage.
 */
void trouver_zone_rec(int ** M, int dim, int i, int j, int * taille, ListeCase * L){
    // On récupère la couleur de la case de départ (la graine)
    int couleur = M[i][j];
    
    // Initialisation d'un pointeur de parcours
    ListeCase courant = *L;
    
    // Remise à zéro de la taille
    *taille = 0;

    // Lancement de la récursion pour remplir la liste L et marquer la zone dans M
    trouver_zone_rec_2(M, dim, i, j, taille, L, couleur);

    // Boucle de restauration :
    // La fonction récursive a mis des -1 dans la matrice. 
    // Cette boucle sert à remettre la vraie couleur dans la matrice M pour que le jeu continue.
    while(courant){
        M[courant->i][courant->j] = couleur;
        courant = courant->suiv;
    }
}

/* * Fonction principale de l'Exercice 1 (Stratégie Naïve / Récursive).
 * Simule le jeu complet.
 */
int sequence_aleatoire_rec(int ** M, Grille * G, int dim, int nbcl, int aff){
    int 
        chgmnt_couleurs = 0, // Compteur de coups joués
        taille = 0,          // Nombre de cases dans la zone inondée actuelle
        ancienne_couleur,
        nouvelle_couleur;

    ListeCase 
        L = NULL, 
        courant;

    // Initialisation de la liste vide
    init_liste(&L);

    // Première détection de la zone Zsg au début du jeu (depuis 0,0)
    trouver_zone_rec(M, dim, 0, 0, &taille, &L);

    // Boucle de jeu : Tant que la zone n'a pas envahi toute la grille
    while(taille < dim * dim){
        chgmnt_couleurs++; // Un nouveau tour commence

        ancienne_couleur = M[0][0]; // La couleur actuelle de la zone
        
        // Choix aléatoire d'une nouvelle couleur (différente de l'actuelle)
        do{
            nouvelle_couleur = rand() % nbcl;
        } while(nouvelle_couleur == ancienne_couleur);

        // Mise à jour de la couleur : On parcourt toute la liste de la Zsg
        courant = L;
        while(courant){
            // 1. Mise à jour en mémoire (Matrice)
            M[courant->i][courant->j] = nouvelle_couleur;
            
            // 2. Mise à jour graphique (si demandée)
            if(aff == 1){
                Grille_attribue_couleur_case(G, courant->i, courant->j, nouvelle_couleur);
                // Grille_redessine_Grille;
                // usleep(5000);

                // Grille_attente_touche();
            }

            courant = courant->suiv;
        }

        // Rafraîchissement de la fenêtre graphique
        if(aff == 1){
            Grille_redessine_Grille(G);
            Grille_attente_touche();
        }

        // --- C'est ici que l'approche est "Naïve" ---
        // On détruit totalement la liste de la zone connue...
        detruit_liste(&L);
        init_liste(&L);

        // On recalcule tout depuis zéro (case 0,0) pour trouver les nouveaux voisins connectés.
        // C'est coûteux car on re-scanne les mêmes cases à chaque tour.
        trouver_zone_rec(M, dim, 0, 0, &taille, &L);
    }

    // Nettoyage final avant de quitter
    detruit_liste(&L);

    return chgmnt_couleurs; // Retourne le score (nombre de coups)
}