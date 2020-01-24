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
	variable.flag_manger = 0;
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

int pion_restant_tab(VARIABLE_JEU variable, int joueur){
	//int joueur -> attend un 1 ou 2 comme dans l'array
	for(int s=0; s<6; s++){
		for(int k=0; k<5; k++){
			if( variable.array[k][s] == joueur){
				return 1;
			}
		}
	}

	return 0;
}

VARIABLE_JEU affichage_manger_possible(SDL_Surface* ecran, VARIABLE_JEU variable, int arriver_x, int arriver_y){
// Effacer un pion manger et le set dans l'array	

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

int fin_jeu_version_simple(VARIABLE_JEU variable){
	int pion_restant_plateau = -1;

	if(variable.tour%2 == 0){
		pion_restant_plateau = pion_restant_tab( variable, 2 );
		if ( variable.jeton_restant_blanc < 0 && pion_restant_plateau == 0 )
			return 1;
	}else{
		pion_restant_plateau = pion_restant_tab( variable, 1 );
		if ( variable.jeton_restant_noir < 0 && pion_restant_plateau == 0 )
			return 2;
	}

	return 0;

}

VARIABLE_JEU game_jvj(SDL_Surface* ecran, SDL_Event event, MYBOX ma_case, VARIABLE_JEU variable, PARA_JEU para_jeu){

	int mode_manger = -1;

	if (ma_case.ligne != -1 || ma_case.colonne != -1 ){ //Dans le plateau
		if(variable.array[ma_case.ligne][ma_case.colonne] == 0 && variable.flag_manger == 0){ //case libre
			if( variable.pion_select.flag == 0 
				&& (variable.jeton_restant_noir+variable.jeton_restant_blanc > 0) ){
				printf("CAS 1\n");
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
        		if( variable.array[ma_case.ligne][ma_case.colonne] == 0){ // Pion Select + case libre => manger pion
        			printf("CAS 2\n");
        			// printf("depart: %d && %d \n", variable.pion_select.ligne, variable.pion_select.colonne);
        			// printf("arrive: %d && %d \n", ma_case.ligne, ma_case.colonne);
        			if( move_possible(variable.pion_select.ligne, variable.pion_select.colonne, ma_case.ligne, ma_case.colonne) == 1 
        				|| manger_possible(variable, ma_case.ligne, ma_case.colonne) == 1){
	        			
	        			variable.array[variable.pion_select.ligne][variable.pion_select.colonne] = 0;
	        			reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
	        			
	        			variable.array[ma_case.ligne][ma_case.colonne] = ((variable.tour+1)%2)+1;
	    				add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2) );


	    				if(manger_possible(variable, ma_case.ligne, ma_case.colonne) == 1){
	    					printf("CHIDORII\n");
	    					variable=affichage_manger_possible(ecran, variable, ma_case.ligne, ma_case.colonne);
		    				if(variable.tour%2 == 1)
								mode_manger = pion_restant_tab( variable, 2 );
							else
								mode_manger = pion_restant_tab( variable, 1 );

		    				if (mode_manger == 1)
		    					variable.flag_manger = 1;
		    				else{
								variable.tour++;
								variable.flag_manger = 0;
								if(variable.tour%2 == 1){
					        		variable.jeton_restant_noir--;
					            	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_noir);
					        	}else{
					        		variable.jeton_restant_blanc--;
					            	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_blanc);
					            }
		    				}
	    				}else{
	    					variable.tour++;
	    				}

	    				variable.pion_select=init_PION_SELECT(variable.pion_select);
	    				// variable.tour++;
	    				// variable.tour--; // A modifier
        			}
        		}
        	}
		}else{
			if(variable.flag_manger == 1 && para_jeu.mode == 1){
					if( variable.array[ma_case.ligne][ma_case.colonne] == (variable.tour%2)+1 ){
						printf("CAS 3\n");
						reset_case_plateau(ecran, ma_case.ligne, ma_case.colonne);
						variable.array[ma_case.ligne][ma_case.colonne]=0;
						variable.tour++;
						variable.flag_manger = 0;
					}
			}else{
				//Selection de pion pour déplacement
				if( variable.array[ma_case.ligne][ma_case.colonne] != variable.tour%2+1 ){
					printf("CAS 5\n");
					if( variable.pion_select.flag == 0 ){ // Si pas de pion select
							add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2)+2); //changer couleur du pion select
							variable.pion_select=set_PION_SELECT(1, ma_case.ligne, ma_case.colonne);
					}else{ // Si pion select
							reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
				    		add_pion(ecran, variable.pion_select.ligne, variable.pion_select.colonne, (variable.tour)%2 );
							add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2)+2); //changer couleur du pion select
							variable.pion_select=set_PION_SELECT(1, ma_case.ligne, ma_case.colonne);
					}
				}				
			}
		}
	}else{
		//Retirer la selection de déplacement
		//Avec un clic en dehors du plateau
		if(variable.pion_select.flag == 1) {
			variable.pion_select.flag=0;
    		reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
    		add_pion(ecran, variable.pion_select.ligne, variable.pion_select.colonne, (variable.tour%2) );
    		variable.pion_select=init_PION_SELECT(variable.pion_select);
		}

		// int azerty = pion_restant_tab( variable, (variable.tour%2)+1 );
		// printf("azerty: %d \n", azerty);
	}

	// printf("flag: %d \n", variable.pion_select.flag);
	afficher_plateau(variable);

	return variable;
}

int game(SDL_Surface* ecran, PARA_JEU para_jeu){

	SDL_Event event; 
	MYBOX ma_case;
	int continuer = 1;
	int fin_de_jeu=0;
	VARIABLE_JEU variable;

	variable=init_VARIABLE_JEU(variable);
	// variable.jeton_restant_blanc=1;
	// variable.jeton_restant_noir=1;

	while (continuer) {

       	fin_de_jeu = fin_jeu_version_simple(variable);
    	
    	if(fin_de_jeu == 1){
    		printf("Joueur 1 gagnant!\n");
    	}else if(fin_de_jeu == 2){
    		printf("Joueur 2 gagnant!\n");
    	}

		if ( pion_restant_tab( variable, (variable.tour%2)+1 ) == 0 ){
			variable.flag_manger = 0;
		}

		// afficher_plateau(plateau);
		if(variable.flag_manger == 1)
			affichage_tour_joueur(ecran, variable.tour, 1);
		else
			affichage_tour_joueur(ecran, variable.tour, 0);
		
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
	        	ma_case = mybox_plateau(event);
	        	// printf("ligne: %d & %d \n", ma_case.ligne, ma_case.colonne);

	        	// printf("pion_choisie: %d && %d \n", variable.pion_select.ligne, variable.pion_select.colonne);
	        	variable = game_jvj(ecran, event, ma_case, variable, para_jeu);

	        default:
	        break;
        }
      	
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }

    return 0;
}