#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#include"gestion_fenetre.h"

const int LARGEUR = 1600;
const int HAUTEUR = 1200;


int main(int argc, char* argv[]) {
    int x, y;   // coordonnées des pixels à dessiner
    int rayon;  // rayon du cercle 
    double dist; // distance au centre
    
    Uint8 couleur;
    SDL_Window* fenetre;  // pointeur sur fenetre SDL
    SDL_Renderer* rendu;  // rendu associé à la fenetre

    
    SDL_creation_fenetre_et_rendu(&fenetre, &rendu, LARGEUR, HAUTEUR);
       
    // colorie le rendu entre couleur RGBD (0,0,0), i.e. Noir
    // avec transparence 255, i.e. couleur opaque
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);

    // Calcul un rayon au tiers de la fenetre
    if (LARGEUR<=HAUTEUR) rayon=sqrt(LARGEUR*LARGEUR)/3;
    else rayon=sqrt(HAUTEUR*HAUTEUR)/3;

    // Dessin du cercle
    for(x = 0; x < LARGEUR; x++) {
      for(y = 0; y < HAUTEUR; y++) {

	// Test si le pixel (x,y) est dans le cercle
         dist=sqrt((x-(LARGEUR/2.0))*(x-(LARGEUR/2.0))+(y-(HAUTEUR/2.0))*(y-(HAUTEUR/2.0)));

	 // Cree un niveau de gris proportionnel à l'éloignement au centre du cercle
         if (dist<=rayon){
	    couleur = 255*dist/rayon;
         }
         else{
            couleur = 0;
	 }

	 // Dessine un pixel de couleur RGB (couleur, couleur, couleur) opaque
	 // i.e gris avec un niveau de gris égale couleur
         SDL_SetRenderDrawColor(rendu, couleur, couleur, couleur, 255);
         SDL_RenderDrawPoint(rendu, x, y);
	 
      }
    }

    // Mise à jour de l'affichage
    SDL_RenderPresent(rendu);
    
    SDL_attente_fermeture_fenetre_et_fermeture(fenetre, rendu);
        
    return 0;
}
