#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

#include "affichage.h"
#include "couleur.h"
#include "game.h"
#include "main.h"
 
void fond_ecran_degrade(SDL_Surface* ecran){
	SDL_Rect position;
    SDL_FillRect(ecran, NULL, blanc);
	SDL_Surface *lignes[256] = {NULL};

	SDL_Surface* rect = NULL;
	SDL_Rect position_rect;

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	
	position_rect.x = 0;
	position_rect.y = 0;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 0, 255, 255)); 
	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

	SDL_FreeSurface(rect);

	for (int i = 0 ; i <= 255 ; i++)
    	lignes[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, 1, 32, 0, 0, 0, 0);

	for (int i=0; i <= 255; i++) {
	    position.x = 0; // Les lignes sont à gauche (abscisse de 0)
	    position.y = i; // La position verticale dépend du numéro de la ligne
	    
	    SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, 0, i, i)); // Dessin
	    SDL_BlitSurface(lignes[i], NULL, ecran, &position); // Collage
	}

	for (int i=0; i <= 255; i++) {
	    position.x = 0; // Les lignes sont à gauche (abscisse de 0)
	    position.y = HEIGHT-i; // La position verticale dépend du numéro de la ligne
	    
	    SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, 0, i, i)); // Dessin
	    SDL_BlitSurface(lignes[i], NULL, ecran, &position); // Collage
	}

 	for (int i = 0 ; i <= 255 ; i++) // Free le fond ecran 
	    SDL_FreeSurface(lignes[i]);
}

void fond_ecran_noir(SDL_Surface* ecran){

	SDL_Surface* rect = NULL;
	SDL_Rect position_rect;

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	
	position_rect.x = 0;
	position_rect.y = 0;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

	SDL_FreeSurface(rect);

}

void fond_ecran_degrade_noir(SDL_Surface* ecran){
	SDL_Rect position;
    SDL_FillRect(ecran, NULL, blanc);
	SDL_Surface *lignes[256] = {NULL};

	for (int i = 0 ; i <= 255 ; i++)
    	lignes[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, 1, 32, 0, 0, 0, 0);

	for (int i=0; i <= 255; i++) {
	    position.x = 0; // Les lignes sont à gauche (abscisse de 0)
	    position.y = i; // La position verticale dépend du numéro de la ligne
	    
	    SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, i, i, i)); // Dessin
	    SDL_BlitSurface(lignes[i], NULL, ecran, &position); // Collage
	}

	for (int i=0; i <= 255; i++) {
	    position.x = 0; // Les lignes sont à gauche (abscisse de 0)
	    position.y = HEIGHT-i; // La position verticale dépend du numéro de la ligne
	    
	    SDL_FillRect(lignes[i], NULL, SDL_MapRGB(ecran->format, i, i, i)); // Dessin
	    SDL_BlitSurface(lignes[i], NULL, ecran, &position); // Collage
	}

 	for (int i = 0 ; i <= 255 ; i++) // Free le fond ecran 
	    SDL_FreeSurface(lignes[i]);
}

void ecran_principal(SDL_Surface* ecran){

	SDL_Surface *titre = NULL;
	// *fond = NULL;
	SDL_Surface *texte_jvj=NULL, *texte_jvia=NULL, *texte_score=NULL, *texte_regle=NULL, *texte_quit=NULL;
	SDL_Surface *bouton_jvj=NULL, *bouton_jvia=NULL, *bouton_score=NULL, *bouton_regle=NULL, *bouton_quit=NULL;
	SDL_Rect pos_bouton_jvj, pos_bouton_jvia, pos_bouton_score, pos_bouton_regle, pos_bouton_quit;
	SDL_Rect pos_texte;
	TTF_Font *police = NULL, *police_titre = NULL;
	SDL_Color couleurNoire = {0, 0, 0};

	fond_ecran_degrade(ecran);

	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("asman.ttf", 30);
	police_titre = TTF_OpenFont("Beech.ttf", 50);
	titre = TTF_RenderUTF8_Blended(police_titre, "Yote", couleurNoire);
	texte_jvj = TTF_RenderUTF8_Blended(police, "Joueur contre Joueur", couleurNoire);
	texte_jvia = TTF_RenderUTF8_Blended(police, "Joueur contre Ordinateur", couleurNoire);
	texte_score = TTF_RenderUTF8_Blended(police, "Tableau des scores", couleurNoire);
	texte_regle = TTF_RenderUTF8_Blended(police, "Regle", couleurNoire);
	texte_quit = TTF_RenderUTF8_Blended(police, "Quitter", couleurNoire);


	bouton_jvj = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_jvia = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_score = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_regle = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_quit = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 200, 150, 0);

	pos_bouton_jvj.x = 250; pos_bouton_jvj.y = 180;
	pos_bouton_jvia.x = 250; pos_bouton_jvia.y = 250;
	pos_bouton_score.x = 250; pos_bouton_score.y = 320;
	pos_bouton_regle.x = 250; pos_bouton_regle.y = 390;
	pos_bouton_quit.x = 250; pos_bouton_quit.y = 460;

    SDL_FillRect(bouton_jvj, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_jvj, NULL, ecran, &pos_bouton_jvj); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_jvia, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_jvia, NULL, ecran, &pos_bouton_jvia); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_score, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_score, NULL, ecran, &pos_bouton_score); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_regle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_regle, NULL, ecran, &pos_bouton_regle); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_quit, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_quit, NULL, ecran, &pos_bouton_quit); // Collage de la surface sur l'écran

    // pos_texte.x = 0;
    // pos_texte.y = 0;
    // SDL_BlitSurface(fond, NULL, ecran, &pos_texte); /* Blit du fond */

    pos_texte.x = 350;
    pos_texte.y = 65;
    SDL_BlitSurface(titre, NULL, ecran, &pos_texte); /* Blit du texte */

    pos_texte.x = 271;
    pos_texte.y = 192;
    SDL_BlitSurface(texte_jvj, NULL, ecran, &pos_texte); /* Blit du texte */

    pos_texte.x = 255;
    pos_texte.y = 265;
    SDL_BlitSurface(texte_jvia, NULL, ecran, &pos_texte); /* Blit du texte */
    
    pos_texte.x = 288;
    pos_texte.y = 332;
    SDL_BlitSurface(texte_score, NULL, ecran, &pos_texte); /* Blit du texte */
    
    pos_texte.x = 355;
    pos_texte.y = 405;
    SDL_BlitSurface(texte_regle, NULL, ecran, &pos_texte); /* Blit du texte */

	pos_texte.x = 350;
    pos_texte.y = 472;
    SDL_BlitSurface(texte_quit, NULL, ecran, &pos_texte); /* Blit du texte */
    SDL_Flip(ecran);

	//Free
	SDL_FreeSurface(titre);
    SDL_FreeSurface(texte_jvj);
    SDL_FreeSurface(texte_jvia);
    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(texte_regle);
    SDL_FreeSurface(texte_quit);

    SDL_FreeSurface(bouton_jvj);
    SDL_FreeSurface(bouton_jvia);
    SDL_FreeSurface(bouton_score);
    SDL_FreeSurface(bouton_regle);
    SDL_FreeSurface(bouton_quit);
    	
    TTF_CloseFont(police);
    TTF_Quit();
}

// PARA_JEU ecran_jvj(SDL_Surface* ecran){
// 	PARA_JEU para_jeu;
// 	para_jeu=init_PARA_JEU(para_jeu);

// 	SDL_Surface *titre = NULL, *suivant = NULL;
// 	SDL_Surface *bouton_suivant=NULL;
// 	SDL_Rect pos_texte, pos_bouton_suivant;
// 	TTF_Font *police = NULL;
// 	SDL_Color couleurNoire = {0, 0, 0};

// 	fond_ecran_degrade(ecran);
// 	TTF_Init();

// 	bouton_suivant = SDL_CreateRGBSurface(SDL_HWSURFACE, 180, 55, 32, 100, 20, 50, 0);

// 	pos_bouton_suivant.x = 240; pos_bouton_suivant.y = 390;

// 	SDL_FillRect(bouton_suivant, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
//     SDL_BlitSurface(bouton_suivant, NULL, ecran, &pos_bouton_suivant); 

// 	// fond = IMG_Load("moraira.jpg");
// 	police = TTF_OpenFont("asman.ttf", 40);

// 	titre = TTF_RenderUTF8_Blended(police, "Joueur contre Joueur", couleurNoire);
// 	suivant = TTF_RenderUTF8_Blended(police, "Suivant", couleurNoire);

// 	pos_texte.x = 250;
//     pos_texte.y = 65;
//     SDL_BlitSurface(titre, NULL, ecran, &pos_texte); 

//     pos_texte.x = 250;
//     pos_texte.y = 400;
//     SDL_BlitSurface(suivant, NULL, ecran, &pos_texte);

// 	TTF_CloseFont(police);
//     TTF_Quit();
//     SDL_FreeSurface(titre);
//     SDL_FreeSurface(suivant);
//     SDL_FreeSurface(bouton_suivant);

//     return para_jeu;
// }

void ecran_jvj(SDL_Surface* ecran){
	SDL_Surface *titre= NULL, *texte_joueur=NULL, *bouton_j1=NULL, *texte_joueur2=NULL, *bouton_j2=NULL, *texte_mode=NULL,*nomJoueur1=NULL, *nomJoueur2=NULL;
	SDL_Surface *texte_modenormal=NULL, *texte_modevariante, *bouton_modenormal=NULL, *bouton_modevariante=NULL, *bouton_valider=NULL, *bouton_annuler=NULL, *texte_valider=NULL, *texte_annuler=NULL;
	SDL_Rect pos_texte, pos_j1, pos_bouton_j1, pos_j2, pos_bouton_j2, pos_mode, pos_modenormal, pos_modevariante,posNomJoueur1,posNomJoueur2;
	SDL_Rect pos_bouton_modenormal, pos_bouton_modevariante, pos_bouton_valider, pos_bouton_annuler, pos_texte_valider, pos_texte_annuler;
	TTF_Font *police, *police_titre = NULL;
	SDL_Color couleurNoire = {0, 0, 0};

	fond_ecran_degrade(ecran);
	TTF_Init();
	police_titre = TTF_OpenFont("Beech.ttf", 50);
	police = TTF_OpenFont("asman.ttf", 20);

	titre = TTF_RenderUTF8_Blended(police_titre, "Joueur contre Joueur", couleurNoire);
	texte_joueur = TTF_RenderUTF8_Blended(police, "Joueur 1", couleurNoire);
	texte_joueur2 = TTF_RenderUTF8_Blended(police, "Joueur 2", couleurNoire);
	texte_mode = TTF_RenderUTF8_Blended(police, "Mode de jeu", couleurNoire);
	texte_modenormal = TTF_RenderUTF8_Blended(police, "Normal", couleurNoire);
	texte_modevariante = TTF_RenderUTF8_Blended(police, "Variante", couleurNoire);
	texte_valider = TTF_RenderUTF8_Blended(police, "OK", couleurNoire);
	texte_annuler = TTF_RenderUTF8_Blended(police, "Retour", couleurNoire);
	nomJoueur1 = TTF_RenderUTF8_Blended(police, "Joueur 1", couleurNoire);
	nomJoueur2 = TTF_RenderUTF8_Blended(police, "Joueur 2", couleurNoire);
	
	bouton_j1 = SDL_CreateRGBSurface(SDL_HWSURFACE, 180, 55, 32, 100, 20, 50, 0);
	bouton_j2 = SDL_CreateRGBSurface(SDL_HWSURFACE, 180, 55, 32, 100, 20, 50, 0);
	bouton_modenormal = SDL_CreateRGBSurface(SDL_HWSURFACE, 65, 55, 32, 100, 20, 50, 0);
	bouton_modevariante = SDL_CreateRGBSurface(SDL_HWSURFACE, 65, 55, 32, 100, 20, 50, 0);
	bouton_valider = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 55, 32, 100, 20, 50, 0);
	bouton_annuler = SDL_CreateRGBSurface(SDL_HWSURFACE, 150, 55, 32, 100, 20, 50, 0);
	
	
	pos_texte.x = 150;				pos_texte.y = 65;
    pos_bouton_j1.x = 160;			pos_bouton_j1.y = 150;
    pos_bouton_j2.x = 460;			pos_bouton_j2.y = 150;
    pos_bouton_modenormal.x = 350;	pos_bouton_modenormal.y = 240;
    pos_bouton_modevariante.x=350;	pos_bouton_modevariante.y = 315; 
    pos_bouton_valider.x = 250;		pos_bouton_valider.y = 450;
    pos_bouton_annuler.x = 415;		pos_bouton_annuler.y = 450;
 
    
    SDL_FillRect(bouton_j1, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_j1, NULL, ecran, &pos_bouton_j1);
    
    SDL_FillRect(bouton_j2, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_j2, NULL, ecran, &pos_bouton_j2);
    
    SDL_FillRect(bouton_modenormal, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_modenormal, NULL, ecran, &pos_bouton_modenormal);
    
    SDL_FillRect(bouton_modevariante, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_modevariante, NULL, ecran, &pos_bouton_modevariante);
    
    SDL_FillRect(bouton_valider, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_valider, NULL, ecran, &pos_bouton_valider);

	SDL_FillRect(bouton_annuler, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_annuler, NULL, ecran, &pos_bouton_annuler);

	SDL_BlitSurface(titre, NULL, ecran, &pos_texte); /* Blit du texte */
	pos_j1.x = 80;					pos_j1.y = 165;
    SDL_BlitSurface(texte_joueur, NULL, ecran, &pos_j1);
    pos_j2.x = 380;					pos_j2.y = 165;
    SDL_BlitSurface(texte_joueur2, NULL, ecran, &pos_j2);
    pos_mode.x = 80;				pos_mode.y = 250;
    SDL_BlitSurface(texte_mode, NULL, ecran, &pos_mode);
    pos_modenormal.x = 250;			pos_modenormal.y = 250;
    SDL_BlitSurface(texte_modenormal, NULL, ecran, &pos_modenormal);
    pos_modevariante.x = 250;		pos_modevariante.y = 325;
    SDL_BlitSurface(texte_modevariante, NULL, ecran, &pos_modevariante);
    pos_texte_valider.x = 285;		pos_texte_valider.y = 465;
    SDL_BlitSurface(texte_valider, NULL, ecran, &pos_texte_valider);
    pos_texte_annuler.x = 460;		pos_texte_annuler.y = 465;
    SDL_BlitSurface(texte_annuler, NULL, ecran, &pos_texte_annuler);
    posNomJoueur1.x = 182;			posNomJoueur1.y = 165;
    SDL_BlitSurface(nomJoueur1, NULL, ecran, &posNomJoueur1);
    posNomJoueur2.x = 482;			posNomJoueur2.y = 165;
    SDL_BlitSurface(nomJoueur2, NULL, ecran, &posNomJoueur2);

    SDL_FreeSurface(titre); SDL_FreeSurface(texte_joueur); SDL_FreeSurface(bouton_j1);
    SDL_FreeSurface(texte_joueur2); SDL_FreeSurface(bouton_j2); SDL_FreeSurface(texte_mode);
    SDL_FreeSurface(nomJoueur1); SDL_FreeSurface(nomJoueur2); SDL_FreeSurface(texte_modenormal);
    SDL_FreeSurface(texte_modevariante); SDL_FreeSurface(bouton_modenormal); SDL_FreeSurface(bouton_modevariante);
    SDL_FreeSurface(bouton_annuler); SDL_FreeSurface(texte_valider); SDL_FreeSurface(texte_annuler);
    SDL_FreeSurface(bouton_valider);
    TTF_CloseFont(police_titre);
	TTF_CloseFont(police);
    TTF_Quit();
}


void affichage_victoire(SDL_Surface* ecran, int joueur){
	SDL_Surface *titre = NULL;
	SDL_Rect position;
	SDL_Surface* rect = NULL;
	TTF_Font *police = NULL;
	SDL_Color couleurBleu = {0, 100, 255};
	SDL_Color couleurRouge = {255, 100, 0};

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 390, 44, 32, 0, 0, 0, 0);

	// fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("Beech.ttf", 40);

	if(joueur == 1)
		titre = TTF_RenderUTF8_Blended(police, "Victoire du Joueur 1 ", couleurBleu);
	else
		titre = TTF_RenderUTF8_Blended(police, "Victoire du Joueur 2 ", couleurRouge);

	position.x = 205;
	position.y = 250;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 30, 30, 30)); 
	SDL_BlitSurface(rect, NULL, ecran, &position); 

	position.x = 215;
    position.y = 255;
    SDL_BlitSurface(titre, NULL, ecran, &position); /* Blit du texte */

    SDL_FreeSurface(rect);
	TTF_CloseFont(police);
    TTF_Quit();
}

void bouton_quit(SDL_Surface* ecran){
	SDL_Surface *titre = NULL;
	SDL_Rect position;
	SDL_Surface* rect = NULL;
	TTF_Font *police = NULL;
	// SDL_Color couleurBleu = {0, 100, 255};
	SDL_Color couleurRouge = {255, 150, 0};

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 105, 34, 32, 0, 0, 0, 0);

	// fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("Beech.ttf", 30);

	titre = TTF_RenderUTF8_Blended(police, "Retour", couleurRouge);

	position.x = 670;
	position.y = 500;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 30, 30, 30)); 
	SDL_BlitSurface(rect, NULL, ecran, &position); 

	position.x = 675;
    position.y = 505;
    SDL_BlitSurface(titre, NULL, ecran, &position); /* Blit du texte */

    SDL_FreeSurface(rect);
	TTF_CloseFont(police);
    TTF_Quit();
}

void bouton_quit2(SDL_Surface* ecran){
	SDL_Surface *titre = NULL;
	SDL_Rect position;
	SDL_Surface* rect = NULL;
	TTF_Font *police = NULL;
	// SDL_Color couleurBleu = {0, 100, 255};
	SDL_Color couleurRouge = {255, 150, 0};

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 105, 34, 32, 0, 0, 0, 0);

	// fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("Beech.ttf", 30);

	titre = TTF_RenderUTF8_Blended(police, "Retour", couleurRouge);

	position.x = 620;
	position.y = 500;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 30, 30, 30)); 
	SDL_BlitSurface(rect, NULL, ecran, &position); 

	position.x = 625;
    position.y = 505;
    SDL_BlitSurface(titre, NULL, ecran, &position); /* Blit du texte */

    SDL_FreeSurface(rect);
	TTF_CloseFont(police);
    TTF_Quit();
}



void ecran_jvia(SDL_Surface* ecran){
	SDL_Surface *titre = NULL;
	 // *fond = NULL;
	SDL_Rect pos_texte;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};

	fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("asman.ttf", 40);

	titre = TTF_RenderUTF8_Blended(police, "Joueur contre IA", couleurNoire);

	pos_texte.x = 250;
    pos_texte.y = 65;
    SDL_BlitSurface(titre, NULL, ecran, &pos_texte); /* Blit du texte */

	TTF_CloseFont(police);
    TTF_Quit();
}

// void reset_case_plateau(SDL_Surface* ecran, int ligne, int colonne){
// 	SDL_Surface* rect = NULL;
// 	SDL_Rect position_rect;

// 	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 69, 69, 32, 0, 0, 0, 0);
	
// 	position_rect.x = 226+colonne*70;
// 	position_rect.y = 51+ligne*70;

// 	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 90, 90, 90)); 
// 	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

// 	SDL_FreeSurface(rect);
// }

void reset_case_plateau(SDL_Surface* ecran, int ligne, int colonne, int design_plateau_numero){
	SDL_Surface* rect = NULL;
	SDL_Rect position_rect;

	position_rect.x = 226+colonne*70;
	position_rect.y = 51+ligne*70;

	if(design_plateau_numero == 0){
		rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 69, 69, 32, 0, 0, 0, 0);
		SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 90, 90, 90));
		SDL_BlitSurface(rect, NULL, ecran, &position_rect);

	}else if(design_plateau_numero == 1){
		rect = SDL_LoadBMP("texture/plateau/chessboard11.bmp");
		SDL_BlitSurface(rect, NULL, ecran, &position_rect);
	}else if(design_plateau_numero == 2){
		rect = SDL_LoadBMP("texture/plateau/chessboard22.bmp");
		SDL_BlitSurface(rect, NULL, ecran, &position_rect);
	}

	SDL_FreeSurface(rect);
}

void jeton_restant(SDL_Surface* ecran, int joueur, int nombre_restant){
	// printf("joueur: %d  &&  nombre_restant: %d \n", joueur, nombre_restant);
	int a_retirer=12-nombre_restant;
	if(joueur==1){
		SDL_Surface *rect=NULL;
		SDL_Rect position_rect;
    	SDL_Rect position_pion;

		SDL_Surface *pion[12] = {NULL};

		rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 300, 32, 0, 0, 0, 0);
		position_rect.x = 50; 
		position_rect.y = 175;

		SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 90, 90, 90)); 
    	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

    	if(nombre_restant<6){
    		for(int s=0; s<nombre_restant; s++){
				position_pion.x=50;
				position_pion.y=175+(50*s);
			    pion[s] = SDL_LoadBMP("texture/pion_noir_50.bmp");
		    	SDL_SetColorKey(pion[s], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s]->format, 0, 0, 255));
			    SDL_BlitSurface(pion[s], NULL, ecran, &position_pion);
			}
    	}else{
			for(int s=0; s<6; s++){
				position_pion.x=50;
				position_pion.y=175+(50*s);
			    pion[s] = SDL_LoadBMP("texture/pion_noir_50.bmp");
		    	SDL_SetColorKey(pion[s], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s]->format, 0, 0, 255));
			    SDL_BlitSurface(pion[s], NULL, ecran, &position_pion);
			}
	    	if(a_retirer<6){
	    		for(int s=0; s<6-a_retirer; s++){
					position_pion.x=100;
					position_pion.y=175+(50*s);
				    pion[s+6] = SDL_LoadBMP("texture/pion_noir_50.bmp");
			    	SDL_SetColorKey(pion[s+6], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s+6]->format, 0, 0, 255));
				    SDL_BlitSurface(pion[s+6], NULL, ecran, &position_pion);
				}
	    	}
    	}
    	SDL_FreeSurface(rect);
    	for(int s=0; s<12; s++)
    		SDL_FreeSurface(pion[s]);

	}else{
		SDL_Surface *rect=NULL;
		SDL_Rect position_rect;
		SDL_Rect position_pion;

		rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 300, 32, 0, 0, 0, 0);
		position_rect.x = 650; 
		position_rect.y = 175;

		SDL_Surface *pion[12] = {NULL};

		SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 90, 90, 90)); 
    	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

    	if(nombre_restant<6){
    		for(int s=0; s<nombre_restant; s++){
				position_pion.x=650;
				position_pion.y=175+(50*s);
			    pion[s] = SDL_LoadBMP("texture/pion_blanc_50.bmp");
		    	SDL_SetColorKey(pion[s], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s]->format, 0, 0, 255));
			    SDL_BlitSurface(pion[s], NULL, ecran, &position_pion);
			}
    	}else{
			for(int s=0; s<6; s++){
				position_pion.x=650;
				position_pion.y=175+(50*s);
			    pion[s] = SDL_LoadBMP("texture/pion_blanc_50.bmp");
		    	SDL_SetColorKey(pion[s], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s]->format, 0, 0, 255));
			    SDL_BlitSurface(pion[s], NULL, ecran, &position_pion);
			}
	    	if(a_retirer<6){
	    		for(int s=0; s<6-a_retirer; s++){
					position_pion.x=700;
					position_pion.y=175+(50*s);
				    pion[s+6] = SDL_LoadBMP("texture/pion_blanc_50.bmp");
			    	SDL_SetColorKey(pion[s+6], SDL_SRCCOLORKEY, SDL_MapRGB(pion[s+6]->format, 0, 0, 255));
				    SDL_BlitSurface(pion[s+6], NULL, ecran, &position_pion);
				}
	    	}
    	}
    	SDL_FreeSurface(rect);
    	for(int s=0; s<12; s++)
    		SDL_FreeSurface(pion[s]);
	}
}

// void design_plateau(SDL_Surface* ecran, int design_plateau_numero){

// 	if(design_plateau_numero==1){

// 		SDL_Surface *plateau=NULL;
// 		SDL_Rect position_plateau, position_horizontale, position_verticale;
// 		SDL_Surface *ligne_horizontale[7] = {NULL};
// 		SDL_Surface *ligne_verticale[6] = {NULL};

// 		plateau = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 420, 32, 0, 0, 0, 0);
		
// 		//ligne horizontale
// 		for (int i = 0; i < 7; i++)
// 	    	ligne_horizontale[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 1, 32, 0, 0, 0, 0);

// 	    //ligne verticale
// 		for (int i = 0; i < 6; i++)
// 	    	ligne_verticale[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 420, 32, 0, 0, 0, 0);


// 		position_plateau.x = 225; 
// 		position_plateau.y = 50;
// 	    SDL_FillRect(plateau, NULL, SDL_MapRGB(ecran->format, 90, 90, 90)); 
// 	    SDL_BlitSurface(plateau, NULL, ecran, &position_plateau); 

// 	    //ligne horizontale
// 	    for (int i = 0 ; i < 7 ; i++) {
// 		    position_horizontale.x = 225; 
// 		    position_horizontale.y = 50+(i*70); 
		    
// 		    SDL_FillRect(ligne_horizontale[i], NULL, SDL_MapRGB(ecran->format, 225, 225, 225));
// 		    SDL_BlitSurface(ligne_horizontale[i], NULL, ecran, &position_horizontale);
// 		}

// 		//ligne verticale
// 	    for (int i = 0 ; i < 6 ; i++) {
// 		    position_verticale.x = 225+(i*70); 
// 		    position_verticale.y = 50; 
		    
// 		    SDL_FillRect(ligne_verticale[i], NULL, SDL_MapRGB(ecran->format, 225, 225, 225)); 
// 		    SDL_BlitSurface(ligne_verticale[i], NULL, ecran, &position_verticale); 
// 		}
// 		// FREE
// 	    //lignes horizontale
// 	    for (int i = 0 ; i < 7 ; i++)
// 	        SDL_FreeSurface(ligne_horizontale[i]);

// 	    //lignes verticale
// 	    for (int i = 0 ; i < 6 ; i++)
// 	        SDL_FreeSurface(ligne_verticale[i]);

// 		// SDL_FreeSurface(joueur1);
// 		// SDL_FreeSurface(joueur2);
// 		// SDL_FreeSurface(plateau);
// 	}
// }

void design_plateau(SDL_Surface* ecran, int design_plateau_numero){

	SDL_Surface *plateau=NULL;
	if(design_plateau_numero==0){


		SDL_Rect position_plateau, position_horizontale, position_verticale;
		SDL_Surface *ligne_horizontale[7] = {NULL};
		SDL_Surface *ligne_verticale[6] = {NULL};

		plateau = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 420, 32, 0, 0, 0, 0);

		//ligne horizontale
		for (int i = 0; i < 7; i++)
	    	ligne_horizontale[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 350, 1, 32, 0, 0, 0, 0);

	    //ligne verticale
		for (int i = 0; i < 6; i++)
	    	ligne_verticale[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 420, 32, 0, 0, 0, 0);


		position_plateau.x = 225;
		position_plateau.y = 50;
	    SDL_FillRect(plateau, NULL, SDL_MapRGB(ecran->format, 90, 90, 90));
	    SDL_BlitSurface(plateau, NULL, ecran, &position_plateau);

	    //ligne horizontale
	    for (int i = 0 ; i < 7 ; i++) {
		    position_horizontale.x = 225;
		    position_horizontale.y = 50+(i*70);

		    SDL_FillRect(ligne_horizontale[i], NULL, SDL_MapRGB(ecran->format, 225, 225, 225));
		    SDL_BlitSurface(ligne_horizontale[i], NULL, ecran, &position_horizontale);
		}

		//ligne verticale
	    for (int i = 0 ; i < 6 ; i++) {
		    position_verticale.x = 225+(i*70);
		    position_verticale.y = 50;

		    SDL_FillRect(ligne_verticale[i], NULL, SDL_MapRGB(ecran->format, 225, 225, 225));
		    SDL_BlitSurface(ligne_verticale[i], NULL, ecran, &position_verticale);
		}
		// FREE
	    //lignes horizontale
	    for (int i = 0 ; i < 7 ; i++)
	        SDL_FreeSurface(ligne_horizontale[i]);

	    //lignes verticale
	    for (int i = 0 ; i < 6 ; i++)
	        SDL_FreeSurface(ligne_verticale[i]);

		// SDL_FreeSurface(joueur1);
		// SDL_FreeSurface(joueur2);
		// SDL_FreeSurface(plateau);
	}else if(design_plateau_numero == 1){
		SDL_Rect position_plateau;

		position_plateau.x = 225;
		position_plateau.y=50;

		plateau = SDL_LoadBMP("texture/plateau/plateau_1.bmp"); //charger light brown plateau_1

		SDL_SetColorKey(plateau, SDL_SRCCOLORKEY, SDL_MapRGB(plateau->format,255,255,255));
		SDL_BlitSurface(plateau,NULL,ecran,&position_plateau);

	}else if(design_plateau_numero == 2){
		SDL_Rect position_plateau;

		position_plateau.x = 225;
		position_plateau.y=50;

		plateau = SDL_LoadBMP("texture/plateau/plateau_2.bmp"); //charger dark brown plateau_1

		SDL_SetColorKey(plateau, SDL_SRCCOLORKEY, SDL_MapRGB(plateau->format,255,255,255));
		SDL_BlitSurface(plateau,NULL,ecran,&position_plateau);
	}

}

void affichage_add_pion(SDL_Surface* ecran, int ligne, int colonne, int couleur){
//Affiche un pion 
//Couleur 0 blanc
//Couleur 1 noir 
//Couleur 2 blanc selectionner
//Couleur 3 noir selectionner
	SDL_Surface *pion = NULL;
	SDL_Rect position_pion;

	position_pion.x=225+colonne*70;
	position_pion.y=50+ligne*70;

	// printf("couleur: %d \n", couleur);
	if(couleur==0){
    	pion = SDL_LoadBMP("texture/pion_blanc_70.bmp");
    	SDL_SetColorKey(pion, SDL_SRCCOLORKEY, SDL_MapRGB(pion->format, 0, 0, 255));
	}else if(couleur==1){
    	pion = SDL_LoadBMP("texture/pion_noir_70.bmp");
    	SDL_SetColorKey(pion, SDL_SRCCOLORKEY, SDL_MapRGB(pion->format, 0, 0, 255));
    }else if(couleur==2){
    	pion = SDL_LoadBMP("texture/pion_blanc_red.bmp");
    	SDL_SetColorKey(pion, SDL_SRCCOLORKEY, SDL_MapRGB(pion->format, 255, 0, 0));
    }else{
    	pion = SDL_LoadBMP("texture/pion_noir_red.bmp");
    	SDL_SetColorKey(pion, SDL_SRCCOLORKEY, SDL_MapRGB(pion->format, 255, 0, 0));
    }

	// SDL_SetColorKey(pion, SDL_SRCCOLORKEY, SDL_MapRGB(pion->format, 0, 0, 255));
    SDL_BlitSurface(pion, NULL, ecran, &position_pion);
    SDL_Flip(ecran);

    SDL_FreeSurface(pion);
}

void affichage_tour_joueur(SDL_Surface* ecran, int tour, int manger){
	SDL_Surface *rect=NULL;
	SDL_Surface *texte_tour = NULL;
	SDL_Rect position;
	TTF_Font *police = NULL;
	SDL_Color couleur_noir = {0, 0, 0};
	// SDL_Color couleur_blanc = {255, 255, 255};

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 126, 23, 32, 0, 0, 0, 0);
	position.x = 337; 
	position.y = 10;

    SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(rect, NULL, ecran, &position); // Collage de la surface sur l'écran

	TTF_Init();
	police = TTF_OpenFont("asman.ttf", 25);

	if(manger == 1)
		if(tour%2 == 1)
			texte_tour = TTF_RenderUTF8_Blended(police, "j1 mange", couleur_noir);
		else
			texte_tour = TTF_RenderUTF8_Blended(police, "j2 mange", couleur_noir);
	else{
		if(tour%2 == 1)
			texte_tour = TTF_RenderUTF8_Blended(police, "tour du j1", couleur_noir);
		else
			texte_tour = TTF_RenderUTF8_Blended(police, "tour du j2", couleur_noir);
	}

	//texte Joueur 1
    position.x = 350;
    position.y = 10;
    SDL_BlitSurface(texte_tour, NULL, ecran, &position); 

    // // FREE
    SDL_FreeSurface(rect);
    SDL_FreeSurface(texte_tour);
    TTF_CloseFont(police);
    TTF_Quit();
}

void ecran_plateau(SDL_Surface* ecran, int design_plateau_numero){
	
	SDL_Surface *joueur1 = NULL, *joueur2 = NULL;
	SDL_Rect position_texte;
	TTF_Font *police = NULL, *police_joueur = NULL;
	//SDL_Color couleur_noir = {0, 0, 0};
	SDL_Color couleur_bleu = {0, 100, 255};


	fond_ecran_degrade(ecran);

	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("asman.ttf", 30);
	police_joueur = TTF_OpenFont("Beech.ttf", 40);
	joueur1 = TTF_RenderUTF8_Blended(police_joueur, "joueur 1", couleur_bleu);
	joueur2 = TTF_RenderUTF8_Blended(police_joueur, "joueur 2", couleur_bleu);

    //texte Joueur 1
    position_texte.x = 20;
    position_texte.y = 10;
    SDL_BlitSurface(joueur1, NULL, ecran, &position_texte); /* Blit du texte */

    //texte Joueur 2
    position_texte.x = 630;
    position_texte.y = 10;
    SDL_BlitSurface(joueur2, NULL, ecran, &position_texte); /* Blit du texte */

    design_plateau(ecran, design_plateau_numero);

    jeton_restant(ecran, 1, 12);
    jeton_restant(ecran, 2, 12);
    // affichage_tour_joueur(ecran, 1);

    bouton_quit(ecran);

    SDL_Flip(ecran);

	// FREE
    TTF_CloseFont(police);
    TTF_Quit();
}

// void ecran_score(SDL_Surface* ecran){
// 	SDL_Surface *titre = NULL;
// 	 // *fond = NULL;
// 	SDL_Rect pos_texte;
// 	TTF_Font *police = NULL;
// 	SDL_Color couleurNoire = {0, 0, 0};

// 	fond_ecran_degrade(ecran);
// 	TTF_Init();
// 	// fond = IMG_Load("moraira.jpg");
// 	police = TTF_OpenFont("asman.ttf", 40);

// 	titre = TTF_RenderUTF8_Blended(police, "Tableau des scores", couleurNoire);

// 	pos_texte.x = 250;
//     pos_texte.y = 65;
//     SDL_BlitSurface(titre, NULL, ecran, &pos_texte); /* Blit du texte */

// 	TTF_CloseFont(police);
//     TTF_Quit();
// }


int strlen2(char s[]){
	int i=0;
	while(s[i] != '\0'){
		i++;
	}
	return i;
}

// void ecran_score(SDL_Surface* ecran, char* pseudo1, char* pseudo2, int pseudo_present, int duel_presents){
void ecran_score(SDL_Surface* ecran){
	
	SDL_Rect pos_texte1;//titre
	SDL_Rect pos_texte2;//retour
	SDL_Rect pos_texte3;//classement
	SDL_Rect pos_texte4;//historique
	SDL_Rect pos_texte5;//score
	SDL_Surface *bouton_retour = NULL;
	SDL_Surface *titre = NULL;
	SDL_Surface *Classement = NULL;
	SDL_Surface *Historique = NULL;
	SDL_Surface *score = NULL;
	int i=0;
	TTF_Font *police1 = NULL;
	TTF_Font *police2 = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	char chaine[50];
	int taille=0;
	char my_string[50];

	for(int s=0; s<20; s++)
		my_string[s]=' ';	
	
	
	fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police1 = TTF_OpenFont("asman.ttf", 40);
	police2 = TTF_OpenFont("asman.ttf", 20);
	

	titre = TTF_RenderUTF8_Blended(police1, "Tableau des scores", couleurNoire);
	bouton_retour = TTF_RenderUTF8_Blended(police2, "Retour", couleurNoire);
	Classement = TTF_RenderUTF8_Blended(police2, "Classement", couleurNoire);
	Historique = TTF_RenderUTF8_Blended(police2, "Historique", couleurNoire);
	score = TTF_RenderUTF8_Blended(police2, chaine, couleurNoire);

	pos_texte1.x = 250;
    pos_texte1.y = 65;
    pos_texte2.x = 105;
    pos_texte2.y = 455;
    pos_texte3.x = 105;
    pos_texte3.y = 105;
    pos_texte4.x = 405;
    pos_texte4.y = 105;
   
    SDL_BlitSurface(titre, NULL, ecran, &pos_texte1); /* Blit du texte */
    SDL_BlitSurface(bouton_retour, NULL, ecran, &pos_texte2); /* Blit du texte */
    SDL_BlitSurface(Classement, NULL, ecran, &pos_texte3); /* Blit du texte */
    SDL_BlitSurface(Historique, NULL, ecran, &pos_texte4); /* Blit du texte */
 
 	FILE* fichier = NULL;
	fichier = fopen("score.txt","r+");
	fseek(fichier,0,SEEK_SET);
	
	while( (fgets(chaine, 50, fichier) != NULL ) && (i<14) ){
		strcpy(my_string, chaine);
		taille = strlen2(chaine);
		my_string[taille-1]= ' ';

		score = TTF_RenderUTF8_Blended(police2, my_string, couleurNoire);
		// printf("a: %s   ", chaine);
		// printf("taille: %d\n", strlen2(chaine));
		pos_texte5.x = 405;
    	pos_texte5.y = 125+i*20;
		SDL_BlitSurface(score, NULL, ecran, &pos_texte5); /* Blit du texte */
		i=i+1;
		
	}

	fclose(fichier);
	  
	SDL_Rect lh1;
	lh1.x=100;
	lh1.y=100;
	lh1.w=300;
	lh1.h=2;
	SDL_FillRect(ecran,&lh1,0);
	SDL_Rect lh2;
	lh2.x=100;
	lh2.y=120;
	lh2.w=300;
	lh2.h=2;
	SDL_FillRect(ecran,&lh2,0);
	SDL_Rect lh3;
	lh3.x=400;
	lh3.y=120;
	lh3.w=300;
	lh3.h=2;
	SDL_FillRect(ecran,&lh3,0);
	SDL_Rect lh4;
	lh4.x=400;
	lh4.y=100;
	lh4.w=300;
	lh4.h=2;
	SDL_FillRect(ecran,&lh4,0);
	SDL_Rect lh5;
	lh5.x=400;
	lh5.y=400;
	lh5.w=300;
	lh5.h=2;
	SDL_FillRect(ecran,&lh5,0);
	SDL_Rect lh6;
	lh6.x=100;
	lh6.y=400;
	lh6.w=300;
	lh6.h=2;
	SDL_FillRect(ecran,&lh6,0);
	
	SDL_Rect lv1;
	lv1.x=100;
	lv1.y=100;
	lv1.w=2;
	lv1.h=300;
	SDL_FillRect(ecran,&lv1,0);
	SDL_Rect lv2;
	lv2.x=400;
	lv2.y=100;
	lv2.w=2;
	lv2.h=300;
	SDL_FillRect(ecran,&lv2,0);
	SDL_Rect lv3;
	lv3.x=700;
	lv3.y=100;
	lv3.w=2;
	lv3.h=300;
	SDL_FillRect(ecran,&lv3,0);
	SDL_Rect retour1;
	retour1.x=100;
	retour1.y=450;
	retour1.w=80;
	retour1.h=2;
	SDL_FillRect(ecran,&retour1,0);
	SDL_Rect retour2;
	retour2.x=100;
	retour2.y=450;
	retour2.w=2;
	retour2.h=20;
	SDL_FillRect(ecran,&retour2,0);
	SDL_Rect retour3;
	retour3.x=100;
	retour3.y=470;
	retour3.w=80;
	retour3.h=2;
	SDL_FillRect(ecran,&retour3,0);
	SDL_Rect retour4;
	retour4.x=180;
	retour4.y=450;
	retour4.w=2;
	retour4.h=22;
	SDL_FillRect(ecran, &retour4, 0);
	

    SDL_FreeSurface(titre);
    SDL_FreeSurface(bouton_retour);
	TTF_CloseFont(police1);
	TTF_CloseFont(police2);
    TTF_Quit();
	
}

// int pseudo_presents( char* pseudo1, char* pseudo2){
	
// 	int pseudo1_trouver=0;
// 	int pseudo2_trouver=0;
// 	char chaine[50];
	
// 	int taille_pseudo1=strlen(pseudo1);
// 	int taille_pseudo2=strlen(pseudo2);
// 	FILE* fichier = NULL;
	
	
// 	fichier = fopen("score.txt","r+");
// 	while((fgets(chaine,taille_pseudo1+1,fichier)!=NULL)&&(pseudo1_trouver==0)){
// 		if(strstr(chaine,pseudo1)!=NULL){
// 			pseudo1_trouver=1;
// 		}
// 	}

// 	fclose(fichier);
// 	fichier = fopen("score.txt","r+");
// 	while((fgets(chaine,taille_pseudo2+1,fichier)!=NULL)&&(pseudo2_trouver==0)){
// 		if(strstr(chaine,pseudo2)!=NULL){
// 			pseudo2_trouver=1;
// 		}
// 	}
// 	fclose(fichier);
	
// 	if( (pseudo1_trouver==1) && (pseudo2_trouver==1) ){
// 		return 3;
// 	}else if((pseudo1_trouver==1)&&(pseudo2_trouver==0)){
// 		return 1;
// 	}else if((pseudo1_trouver==0)&&(pseudo2_trouver==1)){
// 		return 2;
// 	}else if((pseudo1_trouver==0)&&(pseudo2_trouver==0)){
// 		return 0;
// 	}

// }

// int duel_present( char* pseudo1, char* pseudo2){
// 	char* pseudo;
// 	int taille_pseudo=strlen(pseudo);
// 	int pseudo_trouver=0;
// 	char chaine[50];
// 	pseudo=contraction_pseudo(pseudo1,pseudo2);
	
	
	
// 	FILE* fichier = NULL;
// 	fichier = fopen("score.txt","r+");
	
// 	while((fgets(chaine,taille_pseudo+1,fichier)!=NULL)&&(pseudo_trouver==0)){
// 		if(strstr(chaine,pseudo)!=NULL){
// 			pseudo_trouver=1;
// 		}
// 	}

// 	fclose(fichier);
// 	if(pseudo_trouver==1){
// 		return 1;
// 	}else if(pseudo_trouver==0){
		
// 		return 0;
		
// 	}
// }

// char* contraction_pseudo(char*pseudo1, char*pseudo2){
// 	int taille_pseudo1=strlen(pseudo1);
// 	int taille_pseudo2=strlen(pseudo2);
// 	char* pseudo=NULL;
// 	char* vs=" vs ";
	
// 	pseudo=(char*)malloc((taille_pseudo1+taille_pseudo2)*sizeof(char));
// 	strcpy(pseudo,pseudo1);
// 	strcat(pseudo,vs);
// 	strcat(pseudo,pseudo2);
	
// 	return pseudo;	
// }

// int ecriture_historique_fichier(int duel_presents,char* pseudo1,char* pseudo2,int victoire){
// 	char* pseudo=contraction_pseudo(pseudo1, pseudo2);
// 	int i=0;//tableau classement
// 	int j=0;//itteration reecriture
// 	char chaine[50];
// 	int taille_pseudo=strlen(pseudo);
// 	int pseudo_trouver=0;
// 	int score1=1;
// 	int score2=0;
// 	char*nouveau_pseudo=NULL;
// 	int nouveau_score1=0;
// 	int nouveau_score2=0;
	
// 	FILE* fichier = NULL;
// 	fichier = fopen("score.txt","r+");
// 	if(duel_presents==0){
// 		fseek(fichier,0,SEEK_END);
// 		fputs(pseudo,fichier);
	
// 		fclose(fichier);
	
// 		fichier = fopen("score.txt","r+");
	
// 		if(victoire==1){
// 			nouveau_score1=1;
// 			nouveau_score2=0;
// 			fseek(fichier,0,SEEK_END);
// 			fprintf(fichier," %d-%d\n",nouveau_score1,nouveau_score2);
			
// 		}else if(victoire==2){
// 			nouveau_score1=0;
// 			nouveau_score2=1;
// 			fseek(fichier,0,SEEK_END);
			
// 			fprintf(fichier," %d-%d\n",nouveau_score1,nouveau_score2);
// 		}
// 			fclose(fichier);
			
// 	}else if(duel_presents==1){
// 		while((fgets(chaine,taille_pseudo+1,fichier)!=NULL)&&(pseudo_trouver==0)){
// 			j=j+1;
// 			if(strstr(chaine,pseudo)!=NULL){
// 				pseudo_trouver=1;
// 			}
// 		}
		
// 		fseek(fichier,0,SEEK_SET);
// 			fseek(fichier,j*taille_pseudo,SEEK_SET);
// 			fscanf(fichier,"%d-%d",&score1,&score2);
			
// 			if(victoire==1){
// 				score1=score1+1;
// 			}
// 			if(victoire==2){
// 				score2=score2+1;
// 			}
// 			fseek(fichier,j*taille_pseudo,SEEK_SET);
// 			fprintf(fichier," %d-%d\n",score1,score2);
// 			fclose(fichier);
// 	return 4;
// 	}
// }

// classement* ecriture_classement(void) {
// 	classement* ordre;
// 	ordre=(malloc(30*sizeof(classement)));
	
// 	char joueur1[50];
// 	char joueur2[50];
// 	char vs[3];
// 	int resultat1=0;
// 	int resultat2=0;
// 	int joueur1_classer=0;
// 	int joueur2_classer=0;
// 	int i=0;
// 	int j=0;
	
// 	for(i=0;i<28;i++){
// 		ordre[i].joueur=NULL;
// 		ordre[i].resultat=0;
// 	}

// 	i=0;
// 	FILE* fichier;
// 	fichier = fopen("score.txt","r+");
// 	fseek(fichier,0,SEEK_SET);
// 	while((i<14)||(fscanf(fichier,"%s %s %s %d-%d ",joueur1, vs, joueur2,&resultat1,&resultat2)!=NULL));{
// 		fscanf(fichier,"%s %s %s %d-%d ",joueur1, vs, joueur2,&resultat1,&resultat2);
// 		printf("%s %s %s %d-%d\n",joueur1, vs, joueur2,resultat1,resultat2);
// 		joueur1_classer=0;
// 		joueur2_classer=0;
// 		for(j=0;j<28;j++){
// 			if((joueur1!=ordre[j].joueur)&&(ordre[j].joueur!=NULL)){
				
// 			}else if(joueur1==ordre[j].joueur){
// 				ordre[j].resultat=ordre[j].resultat+resultat1;
// 			}else if((joueur1!=ordre[j].joueur)&&(ordre[j].joueur==NULL)&&(joueur1_classer==0)){
// 				ordre[j].joueur=joueur1;
// 				ordre[j].resultat=resultat1;
// 				joueur1_classer=1;
// 			}
// 		}
		
// 		j=0;
	
// 		for(j=0;j<28;j++){
// 			if((joueur2!=ordre[j].joueur)&&(ordre[j].joueur!=NULL)){
			
// 			}else if(joueur2==ordre[j].joueur){
// 				ordre[j].resultat=ordre[j].resultat+resultat2;
				
// 			}else if((joueur2!=ordre[j].joueur)&&(ordre[j].joueur==NULL)&&(joueur2_classer==0)){
// 				ordre[j].joueur=joueur2;
// 				ordre[j].resultat=resultat2;
// 				joueur2_classer=1;
// 			}
// 		}
// 		i=i+1;	
// 	}

// 	fclose(fichier);
// 	i=0;

// 	for(i=0;i<28;i++){
// 		printf("Joueur:%s Score:%d\n",ordre[i].joueur,ordre[i].resultat);
// 	}
// 	i=0;
// 	j=0;
		
// 	return ordre;
// }

void ecran_choix_plateau(SDL_Surface* ecran){
	SDL_Surface *titre = NULL, *choix_1 = NULL, *choix_2 = NULL, *texte_retour = NULL, *bouton_retour = NULL;
	SDL_Rect position_titre, position_choix_1, position_choix_2,position_bouton_retour, position_texte_retour;
	TTF_Font *police_titre = NULL, *police = NULL;
	SDL_Color couleurNoire = {0,0,0};

	fond_ecran_degrade(ecran);

	position_titre.x = 200;
	position_titre.y = 65;
	position_choix_1.x = 240;
	position_choix_1.y = 150;
	position_choix_2.x = 450;
	position_choix_2.y = 150;
	position_bouton_retour.x = 250;
	position_bouton_retour.y = 390;
	position_texte_retour.x = 350;
	position_texte_retour.y = 400;

	TTF_Init();

	police_titre = TTF_OpenFont("Beech.ttf", 50);
	police = TTF_OpenFont("asman.ttf", 30);

	titre = TTF_RenderUTF8_Blended(police_titre, "Choix du plateau", couleurNoire);
	texte_retour = TTF_RenderUTF8_Blended(police, "Retour", couleurNoire);

	bouton_retour = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 200, 150, 0);

	SDL_FillRect(bouton_retour, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));


	position_texte_retour.x = 350;
	position_texte_retour.y = 400;
	SDL_BlitSurface(texte_retour, NULL, ecran, &position_texte_retour);


	choix_1 = SDL_LoadBMP("texture/plateau/chessboard11.bmp");
	choix_2 = SDL_LoadBMP("texture/plateau/chessboard22.bmp");


	SDL_BlitSurface(titre, NULL, ecran, &position_titre);
	SDL_BlitSurface(choix_1, NULL, ecran, &position_choix_1);
	SDL_BlitSurface(choix_2, NULL, ecran, &position_choix_2);
	SDL_BlitSurface(bouton_retour, NULL, ecran, &position_bouton_retour);
	SDL_BlitSurface(texte_retour, NULL, ecran, &position_texte_retour);


	TTF_CloseFont(police_titre);
	TTF_Quit();

	SDL_FreeSurface(titre);
	SDL_FreeSurface(choix_1);
	SDL_FreeSurface(choix_2);
	SDL_FreeSurface(bouton_retour);
	SDL_FreeSurface(texte_retour);
}

void ecran_regles(SDL_Surface* ecran){
	SDL_Surface *titre = NULL, *regles = NULL;
	SDL_Rect position_regles, position_titre;
	TTF_Font *police_titre = NULL;
	// SDL_Color couleurNoire = {0, 0, 0};
	SDL_Color couleurBlanc = {255, 255, 255};

	position_titre.x = 240;          //position du titre
	position_titre.y = 65;
	position_regles.x = 100;    // position des règles
	position_regles.y = 145;

	fond_ecran_noir(ecran);         //fond écran dégradé
	TTF_Init();

	police_titre = TTF_OpenFont("Beech.ttf", 50);
	titre = TTF_RenderUTF8_Blended(police_titre, "Regles du jeu", couleurBlanc);

	regles = SDL_LoadBMP("texture/regles4.bmp");
	SDL_SetColorKey(regles,SDL_SRCCOLORKEY,SDL_MapRGB(regles->format,0,0,0));

	SDL_BlitSurface(titre,NULL,ecran,&position_titre);
	SDL_BlitSurface(regles,NULL,ecran,&position_regles);

	bouton_quit2(ecran);

	TTF_CloseFont(police_titre);

	TTF_Quit();

	SDL_FreeSurface(titre);
	SDL_FreeSurface(regles);
}




//gcc yote.c -o yote -lSDLmain -lSDL


