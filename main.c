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
		returned=0;
		// continuer=0;

	return returned;
}

int main(int argc, char *argv[]) {

	SDL_Surface *ecran = NULL;
	int interface_graphique=4;
	int event_clic;
	int design_plateau=1;
	PARA_JEU para_jeu;

    SDL_Event event; /* La variable contenant l'événement */
    int continuer = 1; /* Notre booléen pour la boucle */

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
    		ecran_plateau(ecran, design_plateau);
    		continuer=game(ecran, para_jeu);
    	}

        switch(event.type) { 
            case SDL_QUIT: //Bouton quitter de la fenêtre 
                continuer = 0;
                break;
            case SDL_KEYUP:
	            if( (event.key.keysym.sym >= 'A' && event.key.keysym.sym <= 'Z')
	            	|| (event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
	   				||	(event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9')){
	            	printf("%c\n", (char) event.key.keysym.sym);
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
	        	}
	        	else if(interface_graphique==1){
	        		if( (250<event.button.x && event.button.x<430) 
						&& (400<event.button.y && event.button.y<450) ){
						interface_graphique=4;
	        		}
	        	}else if(interface_graphique==4){
	        		// BOX ma_case;
	        		// ma_case=plateau(event);
	        		// printf("ligne: %d & %d \n", ma_case.ligne, ma_case.colonne);
	        		// add_pion(ecran, 0, 0, 1);
	        		
	        		// printf("SORTIR\n");
	        	}
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



 



//gcc yote.c -o yote -lSDLmain -lSDL

