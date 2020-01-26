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

struct PARA_JEU{
	char joueur1[20];
	char joueur2[20];
	int mode; // Normal 1 et Variente 2 
};
typedef struct PARA_JEU PARA_JEU;

struct PION_PREC{
	int flag;
	int to_ligne;
	int to_colonne;
	int from_ligne;
	int from_colonne;
};
typedef struct PION_PREC PION_PREC;

struct PION{
	int flag;
	int ligne;
	int colonne;
};
typedef struct PION PION;

struct VARIABLE_JEU{
	int array[10][10];
	int flag_manger;
	int tour;
	int jeton_restant_noir;
	int jeton_restant_blanc;
	PION pion_select; //Pion selectionnée
	PION_PREC pion_blanc; //Dernier mouvement blanc
	PION_PREC pion_noir; // Dernier mouvement noir
};
typedef struct VARIABLE_JEU VARIABLE_JEU;


VARIABLE_JEU init_VARIABLE_JEU(VARIABLE_JEU variable);
PION init_PION(PION pion);
PION set_PION(int flag, int ligne, int colonne);
PION_PREC init_PION_PREC(PION_PREC pion);
PION_PREC set_PION_PREC(int new_flag, int new_to_ligne, int new_to_colonne, int new_from_ligne, int new_from_colonne);

void afficher_plateau(VARIABLE_JEU plateau);
MYBOX mybox_plateau(SDL_Event event);
int move_possible(int pion_x, int pion_y, int arriver_x, int arriver_y);
int manger_possible(VARIABLE_JEU variable, int arriver_x, int arriver_y);
int pion_restant_tab(VARIABLE_JEU variable, int joueur);
int fin_jeu_version_simple(VARIABLE_JEU variable);
int fin_jeu_version_variante(VARIABLE_JEU variable);
int check_move_precedent(MYBOX ma_case, VARIABLE_JEU variable);

VARIABLE_JEU clic_case_libre(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable);
VARIABLE_JEU clic_deplacement_pion(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable,int design_plateau_numero);
VARIABLE_JEU efface_pion_manger(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable, int design_plateau_numero);
VARIABLE_JEU clic_manger_pion(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable, int design_plateau_numero);
VARIABLE_JEU clic_mode_manger(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable, int design_plateau_numero);
VARIABLE_JEU clic_selection_pour_deplacement(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable, int design_plateau_numero);
VARIABLE_JEU clic_retirer_selection(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable, int design_plateau_numero);
VARIABLE_JEU game_jvj(SDL_Surface* ecran, SDL_Event event, MYBOX ma_case, VARIABLE_JEU variable, PARA_JEU para_jeu, int design_plateau_numero);

int game(SDL_Surface* ecran, PARA_JEU para_jeu, int design_plateau_numero);

#endif




