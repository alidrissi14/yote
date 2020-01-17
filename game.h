#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

// #include "affichage.h"
// #include "main.h"

struct MYBOX{
	int ligne; 
	int colonne; 
};
typedef struct MYBOX MYBOX;

MYBOX mybox_plateau(SDL_Event event);
int game(SDL_Surface* ecran);

#endif