#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "main.h"
#include "affichage.h"
// #include "game.h"
// #include "couleur.h"

PARA_JEU init_PARA_JEU(PARA_JEU para_jeu){
	for(int s=0; s<19; s++)
		para_jeu.joueur1[s]=' ';
	para_jeu.joueur1[19]='\0';

	for(int s=0; s<19; s++)
		para_jeu.joueur2[s]=' ';
	para_jeu.joueur2[19]='\0';

	para_jeu.joueur1[0] = 'j';
	para_jeu.joueur1[1] = 'o';
	para_jeu.joueur1[2] = 'u';
	para_jeu.joueur1[3] = 'e';
	para_jeu.joueur1[4] = 'u';
	para_jeu.joueur1[5] = 'r';
	para_jeu.joueur1[6] = '1';
	para_jeu.joueur1[7] = '\0';

	para_jeu.joueur2[0] = 'j';
	para_jeu.joueur2[1] = 'o';
	para_jeu.joueur2[2] = 'u';
	para_jeu.joueur2[3] = 'e';
	para_jeu.joueur2[4] = 'u';
	para_jeu.joueur2[5] = 'r';
	para_jeu.joueur2[6] = '2';
	para_jeu.joueur2[7] = '\0';


	para_jeu.mode = 1;

	return para_jeu;
}

int retour_choix_plateau(SDL_Event event){
	int returned=0;

	if(event.type == SDL_MOUSEBUTTONDOWN){
		if((140 < event.button.x && event.button.x < 210) && (200 < event.button.y && event.button.y < 270))
			returned = 1;
		if((252 < event.button.x && event.button.x < 322) && (200 < event.button.y && event.button.y < 270)){
			returned = 1;
		}
		else if ((350 < event.button.x && event.button.x < 420) && (200 < event.button.y && event.button.y < 270)){
			returned = 1;
		}
		else if ((450 < event.button.x && event.button.x < 520) && (200 < event.button.y && event.button.y < 270)){
			returned = 1;
		}
		else if ((550 < event.button.x && event.button.x < 620) && (200 < event.button.y && event.button.y < 270)){
			returned = 1;
		}
		else if ((650 < event.button.x && event.button.x < 720) && (200 < event.button.y && event.button.y < 270)){
			returned = 1;
		}
 	}

	return returned;
}

int choix_plateau(SDL_Event event){
	int design_plateau_choix=0;

	//SDL_WaitEvent(&event);
	if(event.type == SDL_MOUSEBUTTONDOWN){

		if((140 < event.button.x && event.button.x < 210) && (200 < event.button.y && event.button.y < 270))
			design_plateau_choix = 0;
		if((252 < event.button.x && event.button.x < 322) && (200 < event.button.y && event.button.y < 270)){
			design_plateau_choix = 1; //light brown
		}
		else if ((350 < event.button.x && event.button.x < 420) && (200 < event.button.y && event.button.y < 270)){
			design_plateau_choix = 2; //dark brown
		}
		else if ((450 < event.button.x && event.button.x < 520) && (200 < event.button.y && event.button.y < 270)){
			design_plateau_choix = 3; //blanc et bleu
		}
		else if ((550 < event.button.x && event.button.x < 620) && (200 < event.button.y && event.button.y < 270)){
			design_plateau_choix = 4; // dégradé gris
		}
		else if ((650 < event.button.x && event.button.x < 720) && (200 < event.button.y && event.button.y < 270)){
			design_plateau_choix = 5; //multicolor
		}

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
	else if( (720<event.button.x && event.button.x<790)
		&& (50<event.button.y && event.button.y<120))
			returned=6;
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
	
	if( (160<event.button.x && event.button.x<340) 
		&& (150<event.button.y && event.button.y<205) )
		returned=1;
	else if( (460<event.button.x && event.button.x<640) 
		&& (150<event.button.y && event.button.y<205) )
		returned=2;

	return returned;
}


int main(int argc, char *argv[]) {

	SDL_Surface *ecran = NULL;
	int interface_graphique=0;
	int event_clic;
	// int design_plateau=1;
	PARA_JEU para_jeu;
	char my_string_j1[20];
	char my_string_j2[20];
	int compteur_my_string = 0;
	int design_plateau_numero=0;
	int mode_ecriture=0;

	strcpy(my_string_j1, para_jeu.joueur1);
	strcpy(my_string_j2, para_jeu.joueur2);

    SDL_Event event; /* La variable contenant l'événement */
    int continuer = 1; /* Notre booléen pour la boucle */
    int victoire = 0;

    // int duel_presents=-1;
   
    int jvj_flag_j1 = 0;
    int jvj_flag_j2 = 0;

    SDL_Init(SDL_INIT_VIDEO);
    para_jeu=init_PARA_JEU(para_jeu);
    para_jeu.mode = 2;

    int contre_ia = -1;

    ecran = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre
    SDL_WM_SetCaption("Yote", NULL);

    fond_ecran_degrade(ecran);
    ecran_principal(ecran);

    while (continuer) {

        SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */

    	if(interface_graphique == 0 )
    		ecran_principal(ecran);
    	else if(interface_graphique == 1){
    		contre_ia=1;
    		ecran_jvj(ecran);
    		if(jvj_flag_j1 == 1)
    			ecran_jvj_ecrire_pseudo(ecran, 1, my_string_j1);
    		else
    			ecran_jvj_ecrire_pseudo(ecran, 1, para_jeu.joueur1);
    		if(jvj_flag_j2 == 1)
    			ecran_jvj_ecrire_pseudo(ecran, 2, my_string_j2);
    		else
    			ecran_jvj_ecrire_pseudo(ecran, 2, para_jeu.joueur2);
    		if(para_jeu.mode == 1)
    			coche_case(ecran, 1);
    		else
    			coche_case(ecran, 2);
    	}
    	else if(interface_graphique == 2){
    		contre_ia=2;
    		ecran_jvia(ecran);
    		if(jvj_flag_j1 == 1)
    			ecran_jvj_ecrire_pseudo(ecran, 1, my_string_j1);
    		else
    			ecran_jvj_ecrire_pseudo(ecran, 1, para_jeu.joueur1);
    		if(para_jeu.mode == 1)
    			coche_case(ecran, 1);
    		else
    			coche_case(ecran, 2);
    	}
    	else if(interface_graphique == 3)
    		ecran_score(ecran);
    	else if(interface_graphique == 4) {
    		ecran_plateau(ecran, design_plateau_numero);
    		if(contre_ia == 1){
    			victoire=game(ecran, para_jeu, design_plateau_numero);
    		}
    		if(contre_ia == 2){
    			victoire=game2(ecran, para_jeu, design_plateau_numero);
    		}

    		printf("j1: %s \n", para_jeu.joueur1);
    		printf("j2: %s \n", para_jeu.joueur2);

    		if(victoire==0){
    			interface_graphique=0;
    		}else if(victoire == 1){
    			ecriture_score_victoire(para_jeu.joueur1, para_jeu.joueur2, victoire);
    		}else if (victoire == 2){
    			ecriture_score_victoire(para_jeu.joueur1, para_jeu.joueur2, victoire);
    		}
    		victoire=0;
    		// interface_graphique=0;
    		contre_ia=-1;

    	}else if(interface_graphique == 5){
    		ecran_regles(ecran);
    	}else if(interface_graphique == 6){
    		ecran_choix_plateau(ecran);
    	}

    	// printf("aaaaaaaaa\n");

        switch(event.type) { 
            case SDL_QUIT: //Bouton quitter de la fenêtre 
                continuer = 0;
                break;
            case SDL_KEYUP:
	            if( (event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z')
	            	|| (event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
	   				|| (event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9')){

	            	// printf("event.key.keysym.sym: %c\n", event.key.keysym.sym);
	            	if(interface_graphique == 1 && jvj_flag_j1 == 1){
		            	my_string_j1[compteur_my_string] = event.key.keysym.sym;
		            	compteur_my_string++;

		            	printf("%s \n", my_string_j1);
	            	}else if(interface_graphique == 1 && jvj_flag_j2 == 1){
		            	my_string_j2[compteur_my_string] = event.key.keysym.sym;
		            	compteur_my_string++;

		            	printf("%s \n", my_string_j2);
	            	}else if(interface_graphique == 2 && jvj_flag_j1 == 1){
	            		my_string_j1[compteur_my_string] = event.key.keysym.sym;
		            	compteur_my_string++;

		            	printf("%s \n", my_string_j1);
	            	}
	            } else switch (event.key.keysym.sym){
	                case SDLK_ESCAPE: //Echap
	                    continuer = 0;
	                    break;

	                case SDLK_TAB:
	                	printf("joueur1: %s\n", para_jeu.joueur1);
	                	printf("joueur2: %s\n", para_jeu.joueur2);
	                	break;
	      
	                case SDLK_RETURN: 
	                	if(jvj_flag_j1 == 1){
	                		jvj_flag_j1 = 0;
	                		my_string_j1[compteur_my_string]='\0';
	                		strcpy(para_jeu.joueur1, my_string_j1);
	                		printf("joueur1: %s\n", para_jeu.joueur1);
	                	}

	                	if(jvj_flag_j2 == 1){
	                		jvj_flag_j2 = 0;
	                		my_string_j2[compteur_my_string]='\0';
	                		strcpy(para_jeu.joueur2, my_string_j2);
	                		printf("joueur2: %s\n", para_jeu.joueur2);
	                	}

	                	for(int s=0; s<49; s++){
							my_string_j1[s]=' ';
							my_string_j2[s]=' ';
						}
						my_string_j1[49]='\0';
						my_string_j2[49]='\0';

	                	compteur_my_string=0;
	                	// printf("Touche entree\n");
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
	        		
	        		if((250<event.button.x && event.button.x<350) && (450<event.button.y && event.button.y<505) ) {
						// Suivant/ok
						interface_graphique=4;
					}else if((415<event.button.x && event.button.x<565) && (451<event.button.y && event.button.y<506) ){
	        			// Retour
						interface_graphique=0;
					}else if((356<event.button.x && event.button.x<406) && (244<event.button.y && event.button.y<294) ){
	        			// mode 1
						para_jeu.mode=1;
					}else if((356<event.button.x && event.button.x<406) && (317<event.button.y && event.button.y<367) ){
	        			// mode 2
						para_jeu.mode=2;
					}

					mode_ecriture = ecran_jvj_flag_ecriture(event);
					if( mode_ecriture == 1){
						ecran_jvj_pseudo_rect(ecran, 1); //flash
						jvj_flag_j1 = 1;
						jvj_flag_j2 = 0;
					}else if( mode_ecriture == 2){
						ecran_jvj_pseudo_rect(ecran, 2); //flash
						jvj_flag_j1 = 0;
						jvj_flag_j2 = 1;
					}
					for(int s=0; s<19; s++){
						my_string_j1[s]=' ';
						my_string_j2[s]=' ';
					}
					my_string_j1[19]='\0';
					my_string_j2[19]='\0';

				}
				else if((interface_graphique==2) ){
	        		
	        		if((250<event.button.x && event.button.x<350) && (450<event.button.y && event.button.y<505) ) {
						// Suivant/ok
						interface_graphique=4;
					}else if((415<event.button.x && event.button.x<565) && (451<event.button.y && event.button.y<506) ){
	        			// Retour
						interface_graphique=0;
					}else if((356<event.button.x && event.button.x<406) && (244<event.button.y && event.button.y<294) ){
	        			// mode 1
						para_jeu.mode=1;
					}else if((356<event.button.x && event.button.x<406) && (317<event.button.y && event.button.y<367) ){
	        			// mode 2
						para_jeu.mode=2;
					}

					mode_ecriture = ecran_jvj_flag_ecriture(event);
					if( mode_ecriture == 1){
						ecran_jvj_pseudo_rect(ecran, 1); //flash
						jvj_flag_j1 = 1;
						jvj_flag_j2 = 0;
					}
					for(int s=0; s<19; s++)
						my_string_j1[s]=' ';
					my_string_j1[19]='\0';
				}
				else if( interface_graphique==3 ){
					if( (620<event.button.x && event.button.x<725) 
	        			&& (500<event.button.y && event.button.y<534) ){
						interface_graphique=0;
					}
				}else if( interface_graphique==5 ){
					if( (620<event.button.x && event.button.x<725) 
	        			&& (500<event.button.y && event.button.y<534) ){
						interface_graphique=0;
					}
				}else if( interface_graphique==6 ){
					if( (250<event.button.x && event.button.x<550) 
	        			&& (390<event.button.y && event.button.y<445) ){
						interface_graphique=0;
					}
					if( retour_choix_plateau(event) )
						interface_graphique=0;

					design_plateau_numero=choix_plateau(event);
					// printf("design_plateau_numero: %d\n", design_plateau_numero);
				}

	        default:
	        break;
        }
    	SDL_Flip(ecran); /* Mise à jour de l'écran */
    }
 	
 	// SDL_FreeSurface(ecran);
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}
 


//gcc yote.c -o yote -lSDLmain -lSDL

