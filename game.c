#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "game.h"
#include "main.h"
#include "couleur.h"

VARIABLE_JEU init_VARIABLE_JEU(VARIABLE_JEU variable){

	for(int s=0; s<6; s++)
		for(int k=0; k<5; k++)
			variable.array[s][k]=0;
		
	variable.jeton_restant_noir = 12;
	variable.jeton_restant_blanc = 12;
	variable.flag_manger = 0;
	variable.tour = 1;

	variable.pion_select=init_PION(variable.pion_select);
	variable.pion_blanc=init_PION_PREC(variable.pion_blanc);
	variable.pion_noir=init_PION_PREC(variable.pion_noir);

	return variable;
}

PION init_PION(PION pion){
	pion.flag = 0;
	pion.ligne = -1;
	pion.colonne = -1;

	return pion;
}

PION set_PION(int flag, int ligne, int colonne){
	PION pion;

	pion.flag = flag;
	pion.ligne = ligne;
	pion.colonne = colonne;

	return pion;
}

PION_PREC init_PION_PREC(PION_PREC pion){
	pion.flag = 0;

	pion.to_ligne = -1;
	pion.to_colonne = -1;

	pion.from_ligne = -1;
	pion.from_colonne = -1;

	return pion;
}

PION_PREC set_PION_PREC(int new_flag, int new_to_ligne, int new_to_colonne, int new_from_ligne, int new_from_colonne){
	PION_PREC pion;

	pion.flag = new_flag;

	pion.to_ligne = new_to_ligne;
	pion.to_colonne = new_to_colonne;

	pion.from_ligne = new_from_ligne;
	pion.from_colonne = new_from_colonne;

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
//Transfort un clic sur l'ecran en coordonnée de plateau
//Uniquement sur le plateau de jeu
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
//Regarde si le pion est peut bouger en +

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
//Regarde si le pion selectionner peut manger le pion
	
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
//Check s'il reste des pions sur le plateau en fonction de joueur
//int joueur -> attend un 1 ou 2 comme dans l'array

	for(int s=0; s<6; s++)
		for(int k=0; k<5; k++)
			if( variable.array[k][s] == joueur)
				return 1;
			
	return 0;
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

int fin_jeu_version_variante(VARIABLE_JEU variable){
	int pion_restant_plateau = -1;

	if(variable.tour%2 == 0){
		pion_restant_plateau = pion_restant_tab( variable, 2 );
		if ( pion_restant_plateau == 0 )
			return 1;
	}else{
		pion_restant_plateau = pion_restant_tab( variable, 1 );
		if ( pion_restant_plateau == 0 )
			return 2;
	}

	return 0;

}

int check_move_precedent(MYBOX ma_case, VARIABLE_JEU variable){
// Vérifie si les parametres du pion précédant sont les mêmes

	int prec_from_ligne;
	int prec_from_colonne;

	int prec_to_ligne;
	int prec_to_colonne;

	int from_ligne = variable.pion_select.ligne;
	int from_colonne = variable.pion_select.colonne;

	int to_ligne = ma_case.ligne;
	int to_colonne = ma_case.colonne;


	if(variable.tour%2 == 1){
		prec_from_ligne = variable. pion_noir. from_ligne;
		prec_from_colonne = variable. pion_noir. from_colonne;

		prec_to_ligne = variable. pion_noir. to_ligne;
		prec_to_colonne = variable. pion_noir. to_colonne;
	}else{
		prec_from_ligne = variable. pion_blanc. from_ligne;
		prec_from_colonne = variable. pion_blanc. from_colonne;

		prec_to_ligne = variable. pion_blanc. to_ligne;
		prec_to_colonne = variable. pion_blanc. to_colonne;
	}

	if(prec_from_ligne == to_ligne 
		&& prec_from_colonne == to_colonne
		&& prec_to_ligne == from_ligne 
		&& prec_to_colonne == from_colonne){
		return 0;	
	}

	return 1;
}

VARIABLE_JEU clic_case_libre(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
// Place un pion sur le plateau
// Retirer dans la réserve

	printf("clic_case_libre\n");

	if(variable.tour%2 == 1 && variable.jeton_restant_noir > 0){
		affichage_add_pion(ecran, ma_case.ligne, ma_case.colonne, variable.tour%2);	
		variable.jeton_restant_noir--;
    	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_noir);
    	variable.array[ma_case.ligne][ma_case.colonne] = 1;
    	variable.pion_noir=init_PION_PREC(variable.pion_noir);
    	variable.tour++;
	}else if (variable.tour%2 == 0 && variable.jeton_restant_blanc > 0){
		affichage_add_pion(ecran, ma_case.ligne, ma_case.colonne, variable.tour%2);	
		variable.jeton_restant_blanc--;
    	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_blanc);
    	variable.array[ma_case.ligne][ma_case.colonne]=2;
    	variable.pion_blanc=init_PION_PREC(variable.pion_blanc);
		variable.tour++;
    }

    return variable;
}

VARIABLE_JEU clic_deplacement_pion(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
// Deplace un pion sur le plateau
// Sur la SDL et l'array

	printf("clic_deplacement_pion\n");

	variable.array[variable.pion_select.ligne][variable.pion_select.colonne] = 0;
	reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
	
	variable.array[ma_case.ligne][ma_case.colonne] = ((variable.tour+1)%2)+1;
	affichage_add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2) );

	return variable;
}

VARIABLE_JEU efface_pion_manger(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
// Effacer un pion manger et le set dans l'array	

	int x = variable.pion_select.ligne;
	int y = variable.pion_select.colonne;
	int arriver_x = ma_case.ligne;
	int arriver_y = ma_case.colonne;

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

VARIABLE_JEU clic_manger_pion(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
// Le clic qui permet de déplacer le pion en mangeant un pion
	
	printf("clic_manger_pion\n");

	int mode_manger = -1;

	variable = clic_deplacement_pion(ecran, ma_case, variable); 
	variable = efface_pion_manger(ecran, ma_case, variable);

	//SI    -> il y a plus de pion sur le terrain 
	//ALORS -> mange un pion dans la réserve
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
        	variable.pion_noir=init_PION_PREC(variable.pion_noir);
    	}else{
    		variable.jeton_restant_blanc--;
        	jeton_restant(ecran, variable.tour%2, variable.jeton_restant_blanc);
        	variable.pion_blanc=init_PION_PREC(variable.pion_blanc);
        }
	}

	return variable;
}

VARIABLE_JEU clic_mode_manger(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
// Mange un pion du mode manger (juste après avoir manger un pion)
	if( variable.array[ma_case.ligne][ma_case.colonne] == (variable.tour%2)+1 ){
		printf("clic_manger_pion\n");
		reset_case_plateau(ecran, ma_case.ligne, ma_case.colonne);
		variable.array[ma_case.ligne][ma_case.colonne]=0;
		variable.tour++;
		variable.flag_manger = 0;
	}
	return variable;
}

VARIABLE_JEU clic_selection_pour_deplacement(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
//Selection de pion pour déplacement

	if( variable.array[ma_case.ligne][ma_case.colonne] != variable.tour%2+1 ){
		printf("clic_selection_pour_deplacement\n");
		if( variable.pion_select.flag == 0 ){ // Si pas de déjà pion select
			affichage_add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2)+2); //changer couleur du pion select
			variable.pion_select=set_PION(1, ma_case.ligne, ma_case.colonne);
		}else{ // Si pion déjà select (Déselection)
			reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
    		affichage_add_pion(ecran, variable.pion_select.ligne, variable.pion_select.colonne, (variable.tour)%2 );
			affichage_add_pion(ecran, ma_case.ligne, ma_case.colonne, (variable.tour%2)+2); //changer couleur du pion select
			variable.pion_select=set_PION(1, ma_case.ligne, ma_case.colonne);
		}
	}
	return variable;
}

VARIABLE_JEU clic_retirer_selection(SDL_Surface* ecran, MYBOX ma_case, VARIABLE_JEU variable){
//Retirer la selection de déplacement
//Avec un clic en dehors du plateau
	if(variable.pion_select.flag == 1) {
		variable.pion_select.flag=0;
		reset_case_plateau(ecran, variable.pion_select.ligne, variable.pion_select.colonne);
		affichage_add_pion(ecran, variable.pion_select.ligne, variable.pion_select.colonne, (variable.tour%2) );
		variable.pion_select=init_PION(variable.pion_select);
	}

	return variable;
}

VARIABLE_JEU game_jvj(SDL_Surface* ecran, SDL_Event event, MYBOX ma_case, VARIABLE_JEU variable, PARA_JEU para_jeu){

	int move_precedent = 0; 
	// printf("tour: %d \n", variable.tour);

	if (ma_case.ligne != -1 || ma_case.colonne != -1 ){ //Dans le plateau
		if(variable.array[ma_case.ligne][ma_case.colonne] == 0 && variable.flag_manger == 0){ //case libre
			if( variable.pion_select.flag == 0 ){
				variable=clic_case_libre(ecran, ma_case, variable);
        	}else{
        		// Pion Select + clic sur case libre 

    		    // Pour ne pas faire deux fois le même mouvement
				move_precedent = check_move_precedent(ma_case, variable);
    			
    			if( move_possible(variable.pion_select.ligne, variable.pion_select.colonne, ma_case.ligne, ma_case.colonne) 
    				&& move_precedent == 1){
    				variable = clic_deplacement_pion(ecran, ma_case, variable);
    				
    				if(variable.tour%2 == 1)
    					variable.pion_noir = set_PION_PREC(1, ma_case.ligne, ma_case.colonne, variable.pion_select.ligne, variable.pion_select.colonne);
    				else
						variable.pion_blanc = set_PION_PREC(1, ma_case.ligne, ma_case.colonne, variable.pion_select.ligne, variable.pion_select.colonne);

					variable.pion_select=init_PION(variable.pion_select);
    				variable.tour++;  				
    			}else if( manger_possible(variable, ma_case.ligne, ma_case.colonne) ){
					variable = clic_manger_pion(ecran, ma_case, variable);
					variable.pion_select=init_PION(variable.pion_select);
				}
        	}
		}else{
			if( variable.flag_manger )
				variable = clic_mode_manger(ecran, ma_case, variable);
			else
				variable = clic_selection_pour_deplacement(ecran, ma_case, variable);
		}
	}else
		variable = clic_retirer_selection(ecran, ma_case, variable);

	afficher_plateau(variable);

	return variable;
}



int game(SDL_Surface* ecran, PARA_JEU para_jeu){

	SDL_Event event; 
	MYBOX ma_case;
	int continuer = 1;
	int fin_de_jeu=0;
	VARIABLE_JEU variable;
	int victoire = 0;

	variable=init_VARIABLE_JEU(variable);
	// variable.jeton_restant_blanc=1;
	// variable.jeton_restant_noir=1;

	while (continuer) {

		if(para_jeu.mode == 1)
       		fin_de_jeu = fin_jeu_version_simple(variable);
       	else
       		fin_de_jeu = fin_jeu_version_variante(variable);
    	
    	if(fin_de_jeu == 1 && variable.tour > 2){
    		affichage_victoire(ecran, 1);
    		victoire = 1;
    		// printf("Joueur 1 gagnant!\n");
    	}else if (fin_de_jeu == 2 && variable.tour > 2){
    		affichage_victoire(ecran, 2);
    		victoire = 2;
    		printf("Joueur 2 gagnant!\n");
    	}



    	// printf("blanc: %d \n", variable.jeton_restant_blanc);
    	// printf("noir: %d \n", variable.jeton_restant_noir);
    	

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
	        	if( (670<event.button.x && event.button.x<775) 
					&& (500<event.button.y && event.button.y<534) ){
	    			return victoire;
				}
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
