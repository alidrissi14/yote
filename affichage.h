#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SDL/SDL.h>
#include "game.h"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>


typedef struct{
	char* joueur;
	int resultat;
}classement;

void fond_ecran_degrade(SDL_Surface* ecran);
void fond_ecran_noir(SDL_Surface* ecran);
void fond_ecran_degrade_noir(SDL_Surface* ecran);
void ecran_principal(SDL_Surface* ecran);

// PARA_JEU ecran_jvj(SDL_Surface* ecran);
void ecran_jvj_pseudo_rect(SDL_Surface* ecran, int joueur);
void coche_case(SDL_Surface* ecran, int mode);
void ecran_jvj(SDL_Surface* ecran);

void ecran_jvj_ecrire_pseudo(SDL_Surface* ecran, int joueur, char my_string[50]);
void affichage_victoire(SDL_Surface* ecran, int joueur);

void ecran_jvia(SDL_Surface* ecran);

void ecran_plateau(SDL_Surface* ecran, int design_plateau_numero);
	void reset_case_plateau(SDL_Surface* ecran, int ligne, int colonne, int design_plateau_numero);
	void jeton_restant(SDL_Surface* ecran, int joueur, int nombre_restant);
	void design_plateau(SDL_Surface* ecran, int design_plateau_numero);
	void affichage_add_pion(SDL_Surface* ecran, int ligne, int colonne, int couleur);
	void affichage_tour_joueur(SDL_Surface* ecran, int tour, int manger);

// void ecran_score(SDL_Surface* ecran, char* pseudo1, char* pseudo2, int pseudo_present, int duel_presents);
void ecran_score(SDL_Surface* ecran);
	// int pseudo_presents( char* pseudo1, char* pseudo2);
	int duel_present( char* pseudo1, char* pseudo2);
	char* concat_pseudo(char*pseudo1,char*pseudo2);
	void ecriture_score_victoire(char* pseudo1, char* pseudo2, int victoire);
	// void ecriture_historique_fichier(char* pseudo1, char* pseudo2, int victoire);
	// classement* ecriture_classement(void);

void ecran_choix_plateau(SDL_Surface* ecran);
void ecran_regles(SDL_Surface* ecran);

#endif