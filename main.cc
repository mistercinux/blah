#include <iostream>	
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>       // Les fonctions commencent par SDL
#include <SDL2/SDL_image.h> // Les fonctions commencent par IMG
#include "vaisseau.h"
#include "rocket.h"


// F() Affichage d'erreur SDL ****
void ShowSDLError(const std::string& msg) {  //----------> décaller le & pour voire si ca revient au même
  std::cerr << msg << ": " << IMG_GetError << std::endl;
}


// F() **** Chargement de la textures dans le renderer ****
SDL_Texture *loadTexture(const std::string &path, SDL_Renderer *ren){
  
  SDL_Texture *texture = IMG_LoadTexture(ren, path.c_str());
  printf("Chargement de l'image %s ...\n", path.c_str());

  if (texture == nullptr) {
      ShowSDLError("loadTexture");
      return NULL;
  }

  return texture;
}

// F() **** Préparation de l'affichage de la texture (Avec largeur et hauteur) ****
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {
  
  SDL_Rect destination;
  destination.x = x;
  destination.y = y;
  destination.w = w;
  destination.h = h;
  
  SDL_RenderCopy(ren, tex, NULL, &destination);
}

// F() **** Préparation de l'affichage de la texture (Sans largeur et hauteur) ****
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
  
  SDL_Rect destination;
  destination.x = x;
  destination.y = y;
  
  // Query texture to get its width and height
  SDL_QueryTexture(tex, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(ren, tex, NULL, &destination);
}



// F() **** Positionnement de départ du vaisseau ****
void startPosition(int xscreen, int yscreen, vaisseau *Vaisseau, int who) {
  Vaisseau->setx((xscreen / 2) - (Vaisseau->x_size / 2)); 
  Vaisseau->sety(yscreen - (2*Vaisseau->y_size));         
  Vaisseau->setx_max(xscreen - Vaisseau->x_size);         
  Vaisseau->sety_max(yscreen - Vaisseau->y_size);
  Vaisseau->setdir(who);
}

// F() **** Nettoyage mémoire Rockets ****
int clearRockets (rocket *lst) {

  rocket *prev = NULL;

  while (lst != NULL) {
    prev = lst;
    lst = lst->next;
    std::cout << "Delete: " << prev << std::endl;
    delete prev;
  }
  std::cout << "La mémoire système a été rendue." << std::endl;
  return 1;
}



// F() **** Fonction de tir / gestion de liste chainée ***

int shoot (vaisseau Vaisseau, rocket **pos_rocket, rocket **lst_start) {

  if (*lst_start == NULL) {
    *pos_rocket = new rocket;
    (*pos_rocket)->init(Vaisseau);
    *lst_start = *pos_rocket;
  }
  else {
    (*pos_rocket)->next = new rocket;
    *pos_rocket = (*pos_rocket)->next;
    (*pos_rocket)->init(Vaisseau);
  }
  
  return 1;
}

	    

	    
/*****************************
 *          M A I N          *
 *****************************/

int main() {
  
  const int DELTA    = 5;    // Nombre de pixels par déplacement du vaisseau
  const int SCREEN_W = 640;  // Largeur de fenêtre
  const int SCREEN_H = 480;  // Hauteur de fenêtre
  
  const std::string windowTitle = "Mon titre, blah!";
  const std::string bgPath = "images/fond.png";
  const std::string playerPath = "images/player.png";
  const std::string greenRocketPath = "images/laser_vert.png";
  
  SDL_Window 	*mainWindow = NULL;
  SDL_Renderer 	*mainRenderer = NULL;
  SDL_Texture	*backgroundTex = NULL;
  SDL_Texture	*playerTex = NULL;
  SDL_Texture   *greenRocketTex = NULL;
  
  vaisseau       Vaisseau;
  
  rocket        *rocket_lst_start = NULL;
  rocket        *rocket_lst_pos   = NULL;
  rocket        *rocket_driver    = NULL;
  
  const Uint8 *keyState = SDL_GetKeyboardState(NULL); 
  
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
  backgroundTex  = loadTexture(bgPath.c_str(), mainRenderer);
  playerTex 	 = loadTexture(playerPath.c_str(), mainRenderer);
  greenRocketTex = loadTexture(greenRocketPath.c_str(), mainRenderer);
  
  if ((backgroundTex == NULL) | (playerTex == NULL) | (greenRocketTex == NULL)) {
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    ShowSDLError("loadTexture");
    exit(EXIT_FAILURE);
  }

  //initiallisation du vaisseau et positionnement de départ!
  startPosition(SCREEN_W, SCREEN_H, &Vaisseau, PLAYER);
  
  // Boucle principale
  std::cout << "lst_start = " << rocket_lst_start << std::endl << "Appuyez sur la touche ESC pour quitter..." << std::endl;
  
  while (!keyState[SDL_SCANCODE_ESCAPE]) {
    
    SDL_RenderClear(mainRenderer);
    SDL_RenderCopy(mainRenderer, backgroundTex, NULL, NULL);		 	// Background Set
    renderTexture(playerTex, mainRenderer, Vaisseau.getx(), Vaisseau.gety());	// Affiche le vaisseau

    rocket_driver = rocket_lst_start;
    while(rocket_driver != NULL) { // Affichage des rockets si il y en a;
      renderTexture(greenRocketTex, mainRenderer, rocket_driver->getx(), rocket_driver->gety(), 1, 3);
      rocket_driver = rocket_driver->next;
    }
    
    SDL_RenderPresent(mainRenderer);
    SDL_Delay(10);

    SDL_PumpEvents();    // Met à jour la table : 'const Uint8 *keyState = SDL_GetKeyboardState[NULL]'
    if (keyState[SDL_SCANCODE_UP]) {
      Vaisseau.movey(-DELTA);
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
      Vaisseau.movey(+DELTA);
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
      Vaisseau.movex(-DELTA);
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
      Vaisseau.movex(+DELTA);
    }
    if(keyState[SDL_SCANCODE_SPACE]) {
      shoot(Vaisseau, &rocket_lst_pos, &rocket_lst_start);
      std::cout << "Fire..." <<std::endl;
    }
      
  }
  
  
  printf("Programme en cours de fermeture...\n");

  clearRockets(rocket_lst_start);

  SDL_DestroyTexture(backgroundTex);
  SDL_DestroyRenderer(mainRenderer);
  SDL_DestroyWindow(mainWindow);
  SDL_Quit();
  IMG_Quit();
  exit(EXIT_SUCCESS);
}
