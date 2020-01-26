#ifndef MAIN_H
#define MAIN_H

#include "main.h"
#include "affichage.h"
#include "game.h"

#define WIDTH 800
#define HEIGHT 550

PARA_JEU init_PARA_JEU(PARA_JEU para_jeu);
int mouse_ecran_principal(SDL_Event event);
int mouse_ecran_score(SDL_Event event);

#endif