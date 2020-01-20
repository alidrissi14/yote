#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL/SDL.h>
#include "game.h"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

//Prototype de fonction
void fond_ecran_degrade(SDL_Surface* ecran);
void ecran_principal(SDL_Surface* ecran);
// VARIABLE_JEU affichage_manger_possible(SDL_Surface* ecran, VARIABLE_JEU variable, int arriver_x, int arriver_y);
PARA_JEU ecran_jvj(SDL_Surface* ecran);
void ecran_jvia(SDL_Surface* ecran);
void reset_case_plateau(SDL_Surface* ecran, int ligne, int colonne);
void jeton_restant(SDL_Surface* ecran, int joueur, int nombre_restant);
void design_plateau(SDL_Surface* ecran, int design_plateau_numero);
void add_pion(SDL_Surface* ecran, int ligne, int colonne, int couleur);
void affichage_tour_joueur(SDL_Surface* ecran, int tour);
void ecran_plateau(SDL_Surface* ecran, int design_plateau_numero);
void ecran_score(SDL_Surface* ecran);

#endif