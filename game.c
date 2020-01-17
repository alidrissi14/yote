#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "game.h"
#include "main.h"
#include "couleur.h"


MYBOX mybox_plateau(SDL_Event event){
	MYBOX returned;
	returned.colonne = -1;
	returned.ligne = -1;

	if(event.button.x>225 && event.button.x<575 && event.button.y>50 && event.button.y<470){
		returned.colonne = (event.button.x-225) / 70;
		returned.ligne = (event.button.y-50) / 70;
	}

	return returned;
}

int game(SDL_Surface* ecran){

	// printf("game! \n");
	SDL_Event event; 
	int continuer = 1;
	int tour = 1;
	int jeton_restant_noir = 12,  jeton_restant_blanc = 12;
	MYBOX ma_case;

	while (continuer) {

		// printf("tour: %d\n", tour);
        SDL_WaitEvent(&event);

        switch(event.type) { 
            case SDL_QUIT: //Bouton quitter de la fenêtre 
                continuer = 0;
                return 0;
                break;
            case SDL_KEYUP:
            	switch (event.key.keysym.sym){
	                case SDLK_ESCAPE: //Echap
	                    continuer = 0;
	                    return 0;
	                    break;
	                default:
	                break;
	            }
	            break;
	        case SDL_MOUSEBUTTONDOWN:
	        	
	        	ma_case=mybox_plateau(event);
	        	printf("ligne: %d & %d \n", ma_case.ligne, ma_case.colonne);

				if (ma_case.ligne != -1 || ma_case.colonne != -1 ){
					add_pion(ecran, ma_case.ligne, ma_case.colonne, tour%2);
		        	if(tour%2 == 1){
		        		jeton_restant_noir--;
		            	jeton_restant(ecran, tour%2, jeton_restant_noir);
		        	}else{
		        		jeton_restant_blanc--;
		            	jeton_restant(ecran, tour%2, jeton_restant_blanc);
		            }
	            	tour++;
				}

	        default:
	        break;
        }
      	
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }

    return 0;
}