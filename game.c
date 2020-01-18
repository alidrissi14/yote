#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "game.h"
#include "main.h"
#include "couleur.h"

TABLEAU init_plateau(TABLEAU plateau){
	for(int s=0; s<6; s++){
		for(int k=0; k<5; k++){
			plateau.array[s][k]=0;
		}
	}

	return plateau;
}

void afficher_plateau(TABLEAU plateau){
	for(int s=0; s<6; s++){
		for(int k=0; k<5; k++)
			printf(" %d", plateau.array[s][k]);
		printf("\n");
	}
	printf("\n");
}


PION_SELECT init_PION_SELECT(PION_SELECT pion_choisie){
	pion_choisie.flag = 0;
	pion_choisie.ligne = -1;
	pion_choisie.colonne = -1;

	return pion_choisie;
}

// int plateau_case_libre(TABLEAU plateau, int x, int y, int joueur){
// 	int returned=0;

// 	if(plateau.array[x][y]==0)
// 		returned=1;

// 	return returned;
// }


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
	int jeton_restant_noir = 12, jeton_restant_blanc = 12;
	MYBOX ma_case;
	TABLEAU plateau;
	PION_SELECT pion_choisie;

	pion_choisie=init_PION_SELECT(pion_choisie);
	printf("flag: %d \n", pion_choisie.flag);

	plateau=init_plateau(plateau);
	// afficher_plateau(plateau);

	while (continuer) {

		// afficher_plateau(plateau);
		affichage_tour_joueur(ecran, tour);
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
	        	// printf("tour: %d \n", tour%2);
	        	ma_case=mybox_plateau(event);
	        	// printf("ligne: %d & %d \n", ma_case.ligne, ma_case.colonne);

				if (ma_case.ligne != -1 || ma_case.colonne != -1 ){ //Dans le plateau
					if(plateau.array[ma_case.ligne][ma_case.colonne]==0){ //case libre
						if( pion_choisie.flag==0 ){
							printf("CAS 1\n");
							add_pion(ecran, ma_case.ligne, ma_case.colonne, tour%2);
				        	if(tour%2 == 1){
				        		jeton_restant_noir--;
				            	jeton_restant(ecran, tour%2, jeton_restant_noir);
				        	}else{
				        		jeton_restant_blanc--;
				            	jeton_restant(ecran, tour%2, jeton_restant_blanc);
				            }
			            	tour++;
			            	plateau.array[ma_case.ligne][ma_case.colonne]=(tour%2)+1;
		            	}else{
		            		printf("CAS 2\n");
		            		pion_choisie.flag=0;
		            		plateau.array[ma_case.ligne][ma_case.colonne]=(tour%2);
		            		reset_case_plateau(ecran, pion_choisie.ligne, pion_choisie.colonne);
		            	}
					}else{
						if( plateau.array[ma_case.ligne][ma_case.colonne] != tour%2+1 ){
							printf("BON PION\n");
							add_pion(ecran, ma_case.ligne, ma_case.colonne, tour%2+2);
							pion_choisie.flag=1;
						}else
							printf("MAUVAIS PION\n");
					}
				}else{
					if(pion_choisie.flag==1)
						pion_choisie.flag=0;
				}

	        default:
	        break;
        }
      	
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }

    return 0;
}