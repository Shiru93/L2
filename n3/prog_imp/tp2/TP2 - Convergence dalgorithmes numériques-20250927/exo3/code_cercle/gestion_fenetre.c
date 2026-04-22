#include "gestion_fenetre.h"

void SDL_creation_fenetre_et_rendu(SDL_Window** fenetre,  SDL_Renderer** rendu, int largeur, int hauteur){

    // Initialisation de la librairie SDL
    // (i.e. efface les instructions passées s'il y en a)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL init: %s\n", SDL_GetError());
        exit(2);
    }
  
    // Création d'une fenetre centrée
    *fenetre = SDL_CreateWindow("Cercle colore",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          largeur, hauteur,
                                          SDL_WINDOW_SHOWN);
    if (!fenetre) {
        printf("Erreur création fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        exit(2);
    }

    // Créatiom du rendu associé à la fenetre
    *rendu = SDL_CreateRenderer(*fenetre, -1, SDL_RENDERER_ACCELERATED);
    
    if (!*rendu) {
        printf("Erreur création renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*fenetre);
        SDL_Quit();
        exit(2);
    }
    

}    


void SDL_attente_fermeture_fenetre_et_fermeture(SDL_Window* fenetre, SDL_Renderer* rendu){

   // Boucle d'attente de l'évènement fermeture de fenetre
    SDL_Event event;
    int en_cours = 1;
    while(en_cours) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                en_cours = 0;
            }
        }
        SDL_Delay(16);
    }

    // Destruction rendu puis fenetre
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

}
