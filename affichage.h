#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL/SDL.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

//Prototype de fonction
void fond_ecran_degrade(SDL_Surface* ecran);
void ecran_principal(SDL_Surface* ecran);
void ecran_jvj(SDL_Surface* ecran);
void ecran_jvia(SDL_Surface* ecran);
void jeton_restant(SDL_Surface* ecran, int joueur, int nombre_restant);
void design_plateau(SDL_Surface* ecran, int design_plateau_numero);
void add_pion(SDL_Surface* ecran, int ligne, int colonne, int couleur);
void ecran_plateau(SDL_Surface* ecran, int design_plateau_numero);
void ecran_score(SDL_Surface* ecran);

#endif