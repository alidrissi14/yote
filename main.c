#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "affichage.h"
// #include "game.h"
// #include "couleur.h"

PARA_JEU init_PARA_JEU(PARA_JEU para_jeu){
	para_jeu.joueur1[0] = 'a';
	para_jeu.joueur1[1] = 'a';
	para_jeu.joueur1[2] = 'a';

	para_jeu.joueur2[0] = 'b';
	para_jeu.joueur2[1] = 'b';
	para_jeu.joueur2[2] = 'b';

	para_jeu.mode = 1;

	return para_jeu;
}

int retour_choix_plateau(SDL_Event event){
	int returned=0;

	if(event.type == SDL_MOUSEBUTTONDOWN){
		if((240 < event.button.x && event.button.x < 310) && (150 < event.button.y && event.button.y < 220)){
			returned = 1; 
		}
		else if ((450 < event.button.x && event.button.x < 520) && (150 < event.button.y && event.button.y < 220)){
			returned = 1; 
		} 
 	}

	return returned;
}

int choix_plateau(SDL_Event event){
	int design_plateau_choix=0;

	//SDL_WaitEvent(&event);
	if(event.type == SDL_MOUSEBUTTONDOWN){
		if((240 < event.button.x && event.button.x < 310) && (150 < event.button.y && event.button.y < 220)){
			design_plateau_choix = 1; //light brown
		}
		else if ((450 < event.button.x && event.button.x < 520) && (150 < event.button.y && event.button.y < 220)){
			design_plateau_choix = 2; //dark brown
		} 
		// else if (!(250 < event.button.x && event.button.x < 550) && (390 < event.button.y && event.button.y < 445)){
		// 	design_plateau_choix = 0;
		// }

		/*else if ((250 < event.button.x && event.button.x < 550) && (390 < event.button.y && event.button.y < 445))
		{
		design_plateau_choix=0;    // quitter l'ecran options
	}*/
 	}

	return design_plateau_choix;
}

int mouse_ecran_principal(SDL_Event event){
	int returned;

	if( (250<event.button.x && event.button.x<550) 
		&& (180<event.button.y && event.button.y<235) )
		returned=1;
		// interface_graphique=1;

	else if( (250<event.button.x && event.button.x<550) 
		&& (250<event.button.y && event.button.y<305) )
		returned=2;
		// interface_graphique=2;

	else if( (250<event.button.x && event.button.x<550) 
		&& (320<event.button.y && event.button.y<375) )
		returned=3;
		// interface_graphique=3;

	else if( (250<event.button.x && event.button.x<550) 
		&& (390<event.button.y && event.button.y<445) )
		returned=5;
		// continuer=0;
	else if( (250<event.button.x && event.button.x<550) 
		&& (460<event.button.y && event.button.y<515) )
		returned=0;

	return returned;
}

int mouse_ecran_score(SDL_Event event){
	// printf("mouse_ecran_score\n");
	int returned;
	
	if( (100<event.button.x && event.button.x<180) 
		&& (450<event.button.y && event.button.y<470) )
		returned=1;
	else
		returned=2;
		// interface_graphique=2;

	return returned;
}

int ecran_jvj_flag_ecriture(SDL_Event event){
	int returned=0;
	
	if( (80<event.button.x && event.button.x<260) 
		&& (165<event.button.y && event.button.y<220) )
		returned=1;
	else if( (380<event.button.x && event.button.x<560) 
		&& (165<event.button.y && event.button.y<220) )
		returned=2;

	printf("returned: %d\n", returned);
	return returned;
}

int main(int argc, char *argv[]) {

	SDL_Surface *ecran = NULL;
	int interface_graphique=6;
	int event_clic;
	int design_plateau=1;
	PARA_JEU para_jeu;
	char my_string[50];
	int compteur_my_string = 0;
	int design_plateau_numero=0;

	for(int s=0; s<49; s++){
		my_string[s]=' ';
	}
	my_string[49]='\0';


	// char* pseudo1="C";
 //    char* pseudo2="E";
    // int victoire=1;

    SDL_Event event; /* La variable contenant l'événement */
    int continuer = 1; /* Notre booléen pour la boucle */
    int victoire = 0;

    // classement* ordre;
    // int pseudo_present=6;
    // int duel_presents=6;
    // int pseudo_ecrit=6;
    // int jvj_flag_j1 = 0;
    // int jvj_flag_j2 = 0;

    SDL_Init(SDL_INIT_VIDEO);
    para_jeu=init_PARA_JEU(para_jeu);
    para_jeu.mode = 2;

    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Yote", NULL);

    fond_ecran_degrade(ecran);
    ecran_principal(ecran);

    while (continuer) {

        SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */

    	if(interface_graphique == 0 )
    		ecran_principal(ecran);
    	else if(interface_graphique == 1)
    		// para_jeu=ecran_jvj(ecran);
    		ecran_jvj(ecran);
    	else if(interface_graphique == 2)
    		ecran_jvia(ecran);
    	else if(interface_graphique == 3)
    		ecran_score(ecran);
    	else if(interface_graphique == 4) {
    		ecran_plateau(ecran, design_plateau_numero);
    		victoire=game(ecran, para_jeu, design_plateau_numero);
    		// if(pseudo_present==6)
    		// 	pseudo_present=pseudo_presents(para_jeu.joueur1, para_jeu.joueur2);
    		// if(duel_presents==6)
    		// 	duel_presents=duel_present(para_jeu.joueur1, para_jeu.joueur2);

    		if(victoire==0){
    			interface_graphique=0;
    		}else if(victoire == 1){
    	  	// 	if(pseudo_ecrit==6){
    				// pseudo_ecrit=ecriture_historique_fichier(duel_presents, para_jeu.joueur1, para_jeu.joueur2, victoire);
    	  	// 	}
    		}else if (victoire == 2){
    			// if(pseudo_ecrit==6){
    			// 	pseudo_ecrit=ecriture_historique_fichier(duel_presents, para_jeu.joueur1, para_jeu.joueur2, victoire);
    			// }
    		}
    	}else if(interface_graphique == 5){
    		ecran_regles(ecran);
    	}else if(interface_graphique == 6){
    		ecran_choix_plateau(ecran);
    	}

        switch(event.type) { 
            case SDL_QUIT: //Bouton quitter de la fenêtre 
                continuer = 0;
                break;
            case SDL_KEYUP:
	            if( (event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z')
	            	|| (event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
	   				|| (event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9')){

	            	if(interface_graphique == 1){
		            	my_string[compteur_my_string] = event.key.keysym.sym;
		            	compteur_my_string++;

		            	// if(jvj_flag_j1 == 1)
		            	// 	strcpy(para_jeu.joueur1, my_string);
		            	// if(jvj_flag_j1 == 2)
		            	// 	strcpy(para_jeu.joueur2, my_string);

		            	// printf("j1 %d\n", jvj_flag_j1);
		            	// printf("j2 %d\n", jvj_flag_j2);

		            	// printf("j1: %s \n", para_jeu.joueur1);
		            	// printf("j2: %s \n\n", para_jeu.joueur2);
		            	// printf("%s \n", my_string);
	            	}
	            	// printf("%c\n", (char) event.key.keysym.sym);

	            } else switch (event.key.keysym.sym){
	                case SDLK_ESCAPE: //Echap
	                    continuer = 0;
	                    break;
	                default:
	                break;
	            }
	            break;
	        case SDL_MOUSEBUTTONDOWN:
	        	printf("x: %d  y: %d \n", event.button.x, event.button.y);
	        	if(interface_graphique==0){
	        		event_clic=mouse_ecran_principal(event);
	        		if(event_clic==0)
	        			continuer=0;
	        		else
	        			interface_graphique=event_clic;
	        	}else if((interface_graphique==1) ){
	        		// Suivant/ok
	        		if((250<event.button.x && event.button.x<350) && (450<event.button.y && event.button.y<505) )
						interface_graphique=4;

	        		// Retour
	        		if((415<event.button.x && event.button.x<565) && (451<event.button.y && event.button.y<506) )
						interface_graphique=0;
					// if( ecran_jvj_flag_ecriture(event) == 1)
					// 	jvj_flag_j1 == 1;
					// if( ecran_jvj_flag_ecriture(event) == 2)
					// 	jvj_flag_j1 == 1;
				}
				else if((interface_graphique==2) &&((415<event.button.x && event.button.x<565) 
	        			&& (451<event.button.y && event.button.y<506) )){
					interface_graphique=0;
				}
				else if((interface_graphique==3) &&((415<event.button.x && event.button.x<565) 
	        			&& (451<event.button.y && event.button.y<506) )){
					event_clic=mouse_ecran_score(event);
	        		if(event_clic==1)
	        			interface_graphique=0;
				}else if((interface_graphique==5) ){
					if( (620<event.button.x && event.button.x<725) 
	        			&& (500<event.button.y && event.button.y<534) ){
						interface_graphique=0;
					}
				}else if((interface_graphique==6) ){
					if( (250<event.button.x && event.button.x<550) 
	        			&& (390<event.button.y && event.button.y<445) ){
						interface_graphique=0;
					}
					if( retour_choix_plateau(event) )
						interface_graphique=0;

					design_plateau_numero=choix_plateau(event);
					printf("design_plateau_numero: %d\n", design_plateau_numero);
				}
				// else if((interface_graphique=1) && (((161<event.button.x && event.button.x<338) 
				// 		&& (151<event.button.y && event.button.y<205)) ||((461<event.button.x && event.button.x<639) 
				// 		&& (151<event.button.y && event.button.y<205) ) )){

				// }



	        default:
	        break;
        }
        // printf("interface_graphique: %d\n", interface_graphique);
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }
 	
 	SDL_FreeSurface(ecran);
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}

// void frappe_clavier(){

// }



 



//gcc yote.c -o yote -lSDLmain -lSDL

