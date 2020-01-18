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

struct TABLEAU{
	int array[10][10];
	int x; 
	int y;
};
typedef struct TABLEAU TABLEAU;

struct PARA_JEU{
	char joueur1[20];
	char joueur2[20];
	int mode; // Normal 1 et Variente 2 
};
typedef struct MYBOX MYBOX;

struct PION_SELECT{
	int flag;
	int ligne;
	int colonne;
};
typedef struct PION_SELECT PION_SELECT;

TABLEAU init_plateau(TABLEAU plateau);
void afficher_plateau(TABLEAU plateau);
PION_SELECT init_PION_SELECT(PION_SELECT pion_selec);
int plateau_case_libre(TABLEAU plateau, int x, int y, int joueur);
MYBOX mybox_plateau(SDL_Event event);
int game(SDL_Surface* ecran);

#endif