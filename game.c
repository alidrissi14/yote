#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "game.h"
#include "main.h"
#include "couleur.h"

// TABLEAU init_plateau(TABLEAU plateau){
// 	for(int s=0; s<6; s++){
// 		for(int k=0; k<5; k++){
// 			plateau.array[s][k]=0;
// 		}
// 	}

// 	return plateau;
// }

VARIABLE_JEU init_VARIABLE_JEU(VARIABLE_JEU variable){

	for(int s=0; s<6; s++){
		for(int k=0; k<5; k++){
			variable.array[s][k]=0;
		}
	}
	variable.jeton_restant_noir = 12;
	variable.jeton_restant_blanc = 12;
	variable.tour = 1;

	variable.pion_select=init_PION_SELECT(variable.pion_select);

	return variable;
}

PION_SELECT init_PION_SELECT(PION_SELECT pion_choisie){
	pion_choisie.flag = 0;
	pion_choisie.ligne = -1;
	pion_choisie.colonne = -1;

	return pion_choisie;
}

PION_SELECT set_PION_SELECT(int flag, int ligne, int colonne){
	PION_SELECT pion;

	pion.flag = flag;
	pion.ligne = ligne;
	pion.colonne = colonne;

	return pion;
}

void afficher_plateau(VARIABLE_JEU plateau){
	for(int s=0; s<6; s++){
		for(int k=0; k<5; k++)
			printf(" %d", plateau.array[s][k]);
		printf("\n");
	}
	printf("\n");
}

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

int move_possible(int pion_x, int pion_y, int arriver_x, int arriver_y){

	if(pion_x == arriver_x+1 && pion_y == arriver_y)
		return 1;
	else if (pion_x == arriver_x-1 && pion_y == arriver_y)
		return 1;
	else if (pion_y == arriver_y+1 && pion_x == arriver_x)
		return 1;
	else if (pion_y == arriver_y-1 && pion_x == arriver_x)
		return 1;

	return 0;
}	

int manger_possible(VARIABLE_JEU variable, int arriver_x, int arriver_y){
	// printf("manger_possible\n");
	int x = variable.pion_select.ligne;
	int y = variable.pion_select.colonne;

	if(y == arriver_y){
		if( x+2 == arriver_x && variable.array[x+1][y] == (variable.tour%2)+1 )
			return 1;
		if( x-2 == arriver_x && variable.array[x-1][y] == (variable.tour%2)+1 )
			return 1;	
	}
	if(x == arriver_x){
		if( y+2 == arriver_y && variable.array[x][y+1] == (variable.tour%2)+1 )
			return 1;
		if( y-2 == arriver_y && variable.array[x][y-1] == (variable.tour%2)+1 )
			return 1;
	}

	return 0;
}

VARIABLE_JEU affichage_manger_possible(SDL_Surface* ecran, VARIABLE_JEU variable, int arriver_x, int arriver_y){
	printf("affichage\n");

	int x = variable.pion_select.ligne;
	int y = variable.pion_select.colonne;

	if(y == arriver_y){
		if( x+2 == arriver_x && variable.array[x+1][y] == (variable.tour%2)+1 ){
			reset_case_plateau(ecran, x+1, y);
			variable.array[x+1][y]=0;
		}
		if( x-2 == arriver_x && variable.array[x-1][y] == (variable.tour%2)+1 ){
			reset_case_plateau(ecran, x-1, y);
			variable.array[x-1][y]=0;		
		}
	}
	if(x == arriver_x){
		if( y+2 == arriver_y && variable.array[x][y+1] == (variable.tour%2)+1 ){
			reset_case_plateau(ecran, x, y+1);
			variable.array[x][y+1]=0;
		}
		if( y-2 == arriver_y && variable.array[x][y-1] == (variable.tour%2)+1 ){
			reset_case_plateau(ecran, x, y-1);
			variable.array[x][y-1]=0;
		}
	}

	return variable;
}

VARIABLE_JEU game_jvj(SDL_Surface* ecran, SDL_Event event, MYBOX ma_case, VARIABLE_JEU variable, PARA_JEU para_jeu){

	if (ma_case.ligne != -1 || ma_case.colonne != -1 ){ //Dans le plateau
		if(variable.array[ma_case.ligne][ma_case.colonne] == 0){ //case libre
			if( variable.pion_select.flag == 0 ){
				// printf("CAS 1\n");
				// printf("tour %d\n", variable.tour);
				add_pion(ecran, ma_case.ligne, ma_case.colonne, variable.tour%2);
	        	if(variable.tour%2 == 1){
	        		variable.jeton_restant_noir--;
	            	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_noir);
	        	}else{
	        		variable.jeton_restant_blanc--;
	            	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_blanc);
	            }
            	variable.tour++;
            	variable.array[ma_case.ligne][ma_case.colonne]=(variable.tour%2)+1;
        	}else{
        		// printf("CAS 2\n");
        		if( variable.array[ma_case.ligne][ma_case.colonne] == 0){ // Pion Select + case libre => manger pion
        			// printf("depart: %d && %d \n", variable.pion_select.ligne, variable.pion_select.colonne);
        			// printf("arrive: %d && %d \n", ma_case.ligne, ma_case.colonne);
        			if( move_possible(variable.pion_select.ligne, variable.pion_select.colonne, ma_case.ligne, ma_case.colonne) == 1 
        				|| manger_possible(variable, ma_case.ligne, ma_case.colonne) == 1){
	    				if(manger_possible(variable, ma_case.ligne, ma_case.colonne) == 1)
	    					variable=affichage_manger_possible(ecran, variable, ma_case.ligne, ma_case.colonne);
        				variable.pion_select.flag=0;
	    				variable.tour++;
	        			variable.array[variable.pion_select.ligne][variable.pion_select.colonne] = 0;
	        			variable.array[ma_case.ligne][ma_case.colonne] = (variable.tour%2)+1;
	        			reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
	    				add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour+1)%2 );
	    				variable.pion_select=init_PION_SELECT(variable.pion_select);
        			}
        		}
        	}
		}else{
			//Selection de pion pour déplacement
			if( variable.array[ma_case.ligne][ma_case.colonne] != variable.tour%2+1 ){
				add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2)+2); //changer couleur du pion select
				variable.pion_select=set_PION_SELECT(1, ma_case.ligne, ma_case.colonne);
			}
		}
	}else{
		//Retirer la selection de déplacement
		if(variable.pion_select.flag == 1) {
			variable.pion_select.flag=0;
    		reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
    		add_pion(ecran, variable.pion_select.ligne, variable.pion_select.colonne, (variable.tour%2) );
    		variable.pion_select=init_PION_SELECT(variable.pion_select);
		}
	}

	printf("flag: %d \n", variable.pion_select.flag);
	afficher_plateau(variable);

	return variable;
}

int game(SDL_Surface* ecran, PARA_JEU para_jeu){

	SDL_Event event; 
	MYBOX ma_case;
	int continuer = 1;
	VARIABLE_JEU variable;

	variable=init_VARIABLE_JEU(variable);

	while (continuer) {

		// afficher_plateau(plateau);
		affichage_tour_joueur(ecran, variable.tour);
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

	        	printf("pion_choisie: %d && %d \n", variable.pion_select.ligne, variable.pion_select.colonne);

	        	variable=game_jvj(ecran, event, ma_case, variable, para_jeu);

				

	        default:
	        break;
        }
      	
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }

    return 0;
}