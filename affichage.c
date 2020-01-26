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
	SDL_Surface *texte_jvj=NULL, *texte_jvia=NULL, *texte_score=NULL, *texte_quit=NULL;
	SDL_Surface *bouton_jvj=NULL, *bouton_jvia=NULL, *bouton_score=NULL, *bouton_quit=NULL;
	SDL_Rect pos_bouton_jvj, pos_bouton_jvia, pos_bouton_score, pos_bouton_quit;
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
	texte_quit = TTF_RenderUTF8_Blended(police, "Quitter", couleurNoire);


	bouton_jvj = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_jvia = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_score = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);
	bouton_quit = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 200, 150, 0);

	pos_bouton_jvj.x = 250; pos_bouton_jvj.y = 180;
	pos_bouton_jvia.x = 250; pos_bouton_jvia.y = 250;
	pos_bouton_score.x = 250; pos_bouton_score.y = 320;
	pos_bouton_quit.x = 250; pos_bouton_quit.y = 390;

    SDL_FillRect(bouton_jvj, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_jvj, NULL, ecran, &pos_bouton_jvj); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_jvia, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_jvia, NULL, ecran, &pos_bouton_jvia); // Collage de la surface sur l'écran

    SDL_FillRect(bouton_score, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_score, NULL, ecran, &pos_bouton_score); // Collage de la surface sur l'écran

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
    
	pos_texte.x = 350;
    pos_texte.y = 400;
    SDL_BlitSurface(texte_quit, NULL, ecran, &pos_texte); /* Blit du texte */
    SDL_Flip(ecran);

	//Free
	SDL_FreeSurface(titre);
    SDL_FreeSurface(texte_jvj);
    SDL_FreeSurface(texte_jvia);
    SDL_FreeSurface(texte_score);
    SDL_FreeSurface(texte_quit);

    SDL_FreeSurface(bouton_jvj);
    SDL_FreeSurface(bouton_jvia);
    SDL_FreeSurface(bouton_score);
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
	SDL_Surface *titre= NULL, *texte_joueur=NULL, *bouton_j1=NULL, *texte_joueur2=NULL, *bouton_j2=NULL, *texte_mode=NULL;
	SDL_Surface *texte_modenormal=NULL, *texte_modevariante, *bouton_modenormal=NULL, *bouton_modevariante=NULL, *bouton_valider=NULL, *bouton_annuler=NULL, *texte_valider=NULL, *texte_annuler=NULL;
	SDL_Rect pos_texte, pos_j1, pos_bouton_j1, pos_j2, pos_bouton_j2, pos_mode, pos_modenormal, pos_modevariante;
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

void reset_case_plateau(SDL_Surface* ecran, int ligne, int colonne){
	SDL_Surface* rect = NULL;
	SDL_Rect position_rect;

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 69, 69, 32, 0, 0, 0, 0);
	
	position_rect.x = 226+colonne*70;
	position_rect.y = 51+ligne*70;

	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 90, 90, 90)); 
	SDL_BlitSurface(rect, NULL, ecran, &position_rect); 

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

void design_plateau(SDL_Surface* ecran, int design_plateau_numero){

	if(design_plateau_numero==1){

		SDL_Surface *plateau=NULL;
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

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 125, 23, 32, 0, 0, 0, 0);
	position.x = 355; position.y = 10;

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
    position.x = 370;
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

    SDL_Flip(ecran);

	// FREE
    TTF_CloseFont(police);
    TTF_Quit();
}

void ecran_score(SDL_Surface* ecran){
	SDL_Surface *titre = NULL;
	 // *fond = NULL;
	SDL_Rect pos_texte;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};

	fond_ecran_degrade(ecran);
	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("asman.ttf", 40);

	titre = TTF_RenderUTF8_Blended(police, "Tableau des scores", couleurNoire);

	pos_texte.x = 250;
    pos_texte.y = 65;
    SDL_BlitSurface(titre, NULL, ecran, &pos_texte); /* Blit du texte */

	TTF_CloseFont(police);
    TTF_Quit();
}




//gcc yote.c -o yote -lSDLmain -lSDL


