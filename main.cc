#include <iostream>	// Lib de base pour C++
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCREEN_W = 640;		// Largeur de fenêtre
const int SCREEN_H = 480;		// Hauteur de fenêtre

const std::string windowTitle = "Mon titre, blah!";
const std::string bgPath = "images/fond.bmp";	
const std::string playerPath = "images/player.bmp";

// Fonction d'affichage d'erreur SDL
void ShowSDLError(const std::string msg) {
	fprintf(stderr,"%s: %s\n", msg.c_str(), SDL_GetError());
	return;
}

// Fonction de chargement de la textures dans le renderer 
SDL_Texture *LoadSDLSurface(const std::string path, SDL_Renderer *ren){

	SDL_Texture *texture = NULL;
	SDL_Surface *img = SDL_LoadBMP(path.c_str());
	printf("Chargement de l'image %s ...\n", path.c_str());

	if (img != NULL){
		texture = SDL_CreateTextureFromSurface(ren, img);
		SDL_FreeSurface(img);

		if (texture != NULL)
			return texture;
		else { 
			ShowSDLError("CreateTextureFromSurface"); 	
			return NULL;
		}
	}
	else {
		ShowSDLError("SDL_CreateSurface");
		return NULL;
	}

}
 
// Préparation de l'affichage de la texture
void RenderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	// Query texture to get its width and height
	SDL_QueryTexture(tex, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(ren, tex, NULL, &destination);
}


class vaisseau {

	int x_size;
	int y_size;
	int posx;
	int posy;
	int posx_min;
	int posx_max;
	int posy_min;
	int posy_max;
	int player; 	// 1 si c'est le joueur ou un bonus,
			// 0 si c'est un ennemi

	public: 
	void init(SDL_Texture *tex, int kindOf); // kindOf --> set player to 0 or 1

	int getx(void) {
		return posx;
	}

	int gety(void){
		return posy;
	}

	void setx(int delta) {
		posx += delta;
	}

	void sety(int delta) {
		posy += delta;
	}
};

void vaisseau::init(SDL_Texture *tex, int kindOf) {

	player = kindOf;
	SDL_QueryTexture(tex, NULL, NULL, &x_size, &y_size);
	posx = ((::SCREEN_W / 2) - (x_size / 2));
	posy = (::SCREEN_H - (2*y_size));

	posx_min = 0;
        posx_max = (::SCREEN_W - x_size);
	
	if (player) {
		posy_min = 0;
		posy_max = (::SCREEN_H - y_size);
	}
	else {
		posy_min = (0 - y_size);
		posy_max = (::SCREEN_H);
	}

	return;
}

/*****************************
 *          M A I N          *
 *****************************/
 
int main() {

	SDL_Window 	*mainWindow = NULL;
	SDL_Renderer 	*mainRenderer = NULL;
	SDL_Texture	*backgroundTex = NULL;
	SDL_Texture	*playerTex = NULL;

	vaisseau Vaisseau;
	
	
	// Initialisation de SDL
	if(SDL_Init(SDL_INIT_VIDEO)<0) {
		ShowSDLError("SDL_Init");
		exit(EXIT_FAILURE);
	}

	// Création de la fenêtre
	mainWindow = SDL_CreateWindow(windowTitle.c_str(), 100, 100, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);	
	if (mainWindow == NULL){
		ShowSDLError("SDL_CreateWindow");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	// Création du renderer
	mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mainRenderer == NULL){
		ShowSDLError("SDL_CreateRenderer");
		SDL_DestroyWindow(mainWindow);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	// Chargement des textures
	backgroundTex 	= LoadSDLSurface(bgPath.c_str(), mainRenderer); 	
	playerTex 	= LoadSDLSurface(playerPath.c_str(), mainRenderer);

	if ((backgroundTex == NULL) | (playerTex == NULL)) {
		SDL_DestroyRenderer(mainRenderer);
		SDL_DestroyWindow(mainWindow);
		ShowSDLError("LoadSDLSurface");
		exit(EXIT_FAILURE);
	}

	Vaisseau.init(playerTex, 1);
	
	//Boucle principale 
	while(Vaisseau.gety() > 0) {

		SDL_RenderClear(mainRenderer);
		SDL_RenderCopy(mainRenderer, backgroundTex, NULL, NULL);		 	// Background Set
		RenderTexture(playerTex, mainRenderer, Vaisseau.getx(), Vaisseau.gety());	// Affiche le vaisseau
		Vaisseau.sety(-1);
		SDL_RenderPresent(mainRenderer);
		SDL_Delay(50);
	}

	printf("Programme en cours de fermeture...\n");
	SDL_DestroyTexture(backgroundTex);
	SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}
