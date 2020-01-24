#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

// #include "affichage.h"
#include "game.h"

struct MYBOX{
	int ligne; 
	int colonne; 
};
typedef struct MYBOX MYBOX;

// struct TABLEAU{
// 	int array[10][10];
// 	int x; 
// 	int y;
// };
// typedef struct TABLEAU TABLEAU;

struct PARA_JEU{
	char joueur1[20];
	char joueur2[20];
	int mode; // Normal 1 et Variente 2 
};
typedef struct PARA_JEU PARA_JEU;

struct PION_SELECT{
	int flag;
	int ligne;
	int colonne;
};
typedef struct PION_SELECT PION_SELECT;

struct VARIABLE_JEU{
	int array[10][10];
	int flag_manger;
	int tour;
	int jeton_restant_noir;
	int jeton_restant_blanc;
	PION_SELECT pion_select;
};
typedef struct VARIABLE_JEU VARIABLE_JEU;



// TABLEAU init_plateau(TABLEAU plateau);
VARIABLE_JEU init_VARIABLE_JEU(VARIABLE_JEU variable);
PION_SELECT init_PION_SELECT(PION_SELECT pion_choisie);
// PION_SELECT init_PION_SELECT(PION_SELECT pion_selec);
void afficher_plateau(VARIABLE_JEU plateau);
// int plateau_case_libre(TABLEAU plateau, int x, int y, int joueur);
MYBOX mybox_plateau(SDL_Event event);
int move_possible(int pion_x, int pion_y, int arrive_x, int arrive_y);
int manger_possible(VARIABLE_JEU variable, int arriver_x, int arriver_y);
int pion_restant_tab(VARIABLE_JEU variable, int joueur);
VARIABLE_JEU affichage_manger_possible(SDL_Surface* ecran, VARIABLE_JEU variable, int arriver_x, int arriver_y);
VARIABLE_JEU game_jvj(SDL_Surface* ecran, SDL_Event event, MYBOX ma_case, VARIABLE_JEU variable, PARA_JEU para_jeu);
int game(SDL_Surface* ecran, PARA_JEU para_jeu);

#endif