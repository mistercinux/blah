#include <iostream>	
#include <SDL2/SDL.h>       // Les fonctions commencent par SDL
#include <SDL2/SDL_image.h> // Les fonctions commencent par IMG
#include <forward_list>
#include "vaisseau.h"
#include "rocket.h"
#include "gestion_sdl.h"


// F() **** Préparation de l'affichage de la texture (Avec largeur et hauteur) ****
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h) {

  SDL_Rect destination = { .x=x, .y=y, .w=w, .h=h };
  SDL_RenderCopy(ren, tex, NULL, &destination);
}

// F() **** Préparation de l'affichage de la texture (Sans largeur et hauteur) ****
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {

  SDL_Rect destination = { .x=x, .y=y };
  // Query texture to get its width and height
  SDL_QueryTexture(tex, NULL, NULL, &destination.w, &destination.h);
  SDL_RenderCopy(ren, tex, NULL, &destination);
}


// F() **** Nettoyage mémoire des Rockets restants ****
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
  else if (((*pos_rocket)->intervalCheck()) == 1) {
    (*pos_rocket)->next = new rocket;
    *pos_rocket = (*pos_rocket)->next;
    (*pos_rocket)->init(Vaisseau);
  }

  return 1;
}


// F() **** Déplacement des rockets et vaisseaux ennemis ****
int mapIncrementation (rocket **rocketLstStart, int screenW, int screenH) { // Inclure les vaisseaux ennemis par la suite

  rocket *rocketDriver  = NULL;
  rocket *prevRocket    = NULL;

  rocketDriver = *rocketLstStart;
  prevRocket   = *rocketLstStart;

  if(*rocketLstStart == NULL) {
    return 1;
  }

  // Boucle de gestion des rockets*
  while (rocketDriver != NULL) {

    rocketDriver->move();
    //      std::cout << "déplacement de rocket: y = " << rocketDriver->gety() << std::endl; // debug

    if ((rocketDriver->gety() <= (0 - rocketDriver->getWidth())) | (rocketDriver->gety() >= screenH)) {

      rocketDriver = rocketDriver->next;
      if (rocketDriver == NULL) {
	std::cout << "mapIncrementation: Dernière roquette: &rocketDriver = " << rocketDriver << std::endl;
	std::cout << "mapIncrementation: Reinitialisation de la liste..." << std::endl;
	*rocketLstStart = NULL;
      }

      if (prevRocket == *rocketLstStart) { *rocketLstStart = rocketDriver; }
      delete prevRocket;
      std::cout << "mapIncrementation: Roquette effacée" << std::endl;
      prevRocket = rocketDriver;
    }

else { rocketDriver = rocketDriver->next; }

  }

  return 1;
}



/*****************************
 *          M A I N          *
 *****************************/

int main() {

  const int SCREEN_W = 640;  // Largeur de fenêtre
  const int SCREEN_H = 480;  // Hauteur de fenêtre

    int keyMovX =0;
    int keyMovY =0;

  const std::string windowTitle = "Mon titre, blah!";
  const std::string bgPath = "images/fond.png";
  const std::string playerPath = "images/player.png";
  const std::string greenRocketPath = "images/laser_vert.png";

//  SDL_Window 	*mainWindow = NULL;
//  SDL_Renderer 	*mainRenderer = NULL;
//  SDL_Texture	*backgroundTex = NULL;
//  SDL_Texture	*playerTex = NULL;
//  SDL_Texture   *greenRocketTex = NULL;

  vaisseau       Vaisseau;

  std::forward_list<rocket> rocketLst;
  
    gestion_sdl mysdl;
  
  rocket        *rocket_lst_start = NULL;
  rocket        *rocket_lst_pos   = NULL;
  rocket        *rocket_driver    = NULL;

  const Uint8 *keyState = SDL_GetKeyboardState(NULL); 

  // Initialisation de SDL
    mysdl.init((&bgPath)->c_str(), (&playerPath)->c_str(), (&greenRocketPath)->c_str());
  
  //initiallisation du vaisseau et positionnement de départ!
  Vaisseau.start(1, mysdl.getWidth(), mysdl.getHeight()); //1 = player


  // Boucle principale //
  /*********************/

  std::cout << "lst_start = " << rocket_lst_start << std::endl << "Appuyez sur la touche ESC pour quitter..." << std::endl;

  while (!keyState[SDL_SCANCODE_ESCAPE]) {

    mysdl.renderClear();
    SDL_RenderCopy(mysdl.mainRenderer__, mysdl.backgroundTex__, NULL, NULL);		 	// Background Set

    renderTexture(mysdl.playerTex__, mysdl.mainRenderer__, Vaisseau.getx(), Vaisseau.gety());	// Affiche le vaisseau

    rocket_driver = rocket_lst_start;
    while(rocket_driver != NULL) { // Affichage des rockets si il y en a;
      renderTexture(mysdl.greenRocketTex__, mysdl.mainRenderer__, rocket_driver->getx(), rocket_driver->gety(), rocket_driver->getWidth(), rocket_driver->getHeight());
      rocket_driver = rocket_driver->next;
    }

    SDL_RenderPresent(mysdl.mainRenderer__);
    SDL_Delay(5);                               // 10 est une valeur correcte
    SDL_PumpEvents();                           // Met à jour la table : 'const Uint8 *keyState = SDL_GetKeyboardState[NULL]'

    if (keyState[SDL_SCANCODE_DOWN]) {  
      keyMovY += Vaisseau.getSpeed(); 
    }                                  
    if (keyState[SDL_SCANCODE_UP]) {   
      keyMovY -= Vaisseau.getSpeed();     
    }                                  
    if (keyState[SDL_SCANCODE_RIGHT]) {
      keyMovX += Vaisseau.getSpeed();
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
      keyMovX -= Vaisseau.getSpeed();           
    }
    if (keyState[SDL_SCANCODE_SPACE]) {
      shoot(Vaisseau, &rocket_lst_pos, &rocket_lst_start);
    }

    Vaisseau.move(keyMovX, keyMovY);
    mapIncrementation( &rocket_lst_start, SCREEN_W, SCREEN_H);
    keyMovX = keyMovY = 0;
  }


  printf("Programme en cours de fermeture...\n");

  clearRockets(rocket_lst_start);

  exit(EXIT_SUCCESS);
}
