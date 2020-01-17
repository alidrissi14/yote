void ecran_plateau(SDL_Surface* ecran){
	
	SDL_Surface *joueur1 = NULL;
	// *fond = NULL;
	SDL_Surface *texte_jvj=NULL;
	SDL_Surface *bouton_jvj=NULL;
	SDL_Rect pos_bouton_jvj;
	SDL_Rect pos_texte;
	
	TTF_Font *police = NULL, *police_joueur = NULL;
	SDL_Color couleurNoire = {0, 0, 0};

	fond_ecran_degrade(ecran);

	TTF_Init();
	// fond = IMG_Load("moraira.jpg");
	police = TTF_OpenFont("asman.ttf", 30);
	police_joueur1 = TTF_OpenFont("Beech.ttf", 50);
	joueur1 = TTF_RenderUTF8_Blended(police_joueur, "Yote", couleurNoire);
	texte_jvj = TTF_RenderUTF8_Blended(police, "Joueur contre Joueur", couleurNoire);


	bouton_jvj = SDL_CreateRGBSurface(SDL_HWSURFACE, 300, 55, 32, 100, 20, 50, 0);

	pos_bouton_jvj.x = 250; pos_bouton_jvj.y = 180;


    SDL_FillRect(bouton_jvj, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
    SDL_BlitSurface(bouton_jvj, NULL, ecran, &pos_bouton_jvj); // Collage de la surface sur l'écran


    pos_texte.x = 10;
    pos_texte.y = 10;
    SDL_BlitSurface(joueur1, NULL, ecran, &pos_texte); /* Blit du texte */

    pos_texte.x = 271;
    pos_texte.y = 192;
    SDL_BlitSurface(texte_jvj, NULL, ecran, &pos_texte); /* Blit du texte */

    SDL_Flip(ecran);

    TTF_CloseFont(police);
    TTF_Quit();
}