#include <iostream>	
#include <SDL2/SDL.h>       // Les fonctions commencent par SDL
#include <SDL2/SDL_image.h> // Les fonctions commencent par IMG
#include <list>
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


// F() **** Déplacement des rockets et vaisseaux ennemis ****
int mapIncrementation (std::list<rocket>& rocketLst, int screenW, int screenH) { // Inclure les vaisseaux ennemis par la suite

    std::list<rocket>::iterator rocketIt;

    if(rocketLst.size() == 0) { return 1; }

    for(rocketIt = rocketLst.begin(); rocketIt != rocketLst.end(); ++rocketIt)
    {
        rocketIt->move();
        if ((rocketIt->gety() <= (0 - rocketIt->getHeight())) | (rocketIt->gety() >= screenH)) 
        { 
            rocketIt = rocketLst.erase(rocketIt);
        }
    }

    return 1;
}



/*****************************
 *          M A I N          *
 *****************************/

int main() {

    const std::string windowTitle = "Mon titre, blah!";
    const std::string bgPath = "images/fond.png";
    const std::string playerPath = "images/player.png";
    const std::string greenRocketPath = "images/laser_vert.png";

    int playerMovX = 0;
    int playerMovY = 0;
  
    std::list<rocket>           rocketLst;
    std::list<rocket>::iterator rocketIt;
    gestion_sdl                 mysdl;
    // Initialisation de SDL
    mysdl.init( (&bgPath)->c_str(), (&playerPath)->c_str(), (&greenRocketPath)->c_str() );
    vaisseau  Vaisseau( PLAYER, mysdl.getWidth(), mysdl.getHeight() );

    const Uint8 *keyState = SDL_GetKeyboardState(NULL); 


    // Boucle principale //
    /*********************/

    std::cout << "Appuyez sur la touche ESC pour quitter..." << std::endl;

    while (!keyState[SDL_SCANCODE_ESCAPE]) {

        mysdl.renderClear();                                                                        // Vide le renderer
        SDL_RenderCopy(mysdl.mainRenderer__, mysdl.backgroundTex__, NULL, NULL);		 	// Background Set
        renderTexture(mysdl.playerTex__, mysdl.mainRenderer__, Vaisseau.getx(), Vaisseau.gety());	// Affiche le vaisseau

        for(rocketIt = rocketLst.begin(); rocketIt != rocketLst.end(); ++rocketIt)
        {
            renderTexture(mysdl.greenRocketTex__, mysdl.mainRenderer__, rocketIt->getx(), rocketIt->gety(), rocketIt->getWidth(), rocketIt->getHeight());
        }

        SDL_RenderPresent(mysdl.mainRenderer__);
        SDL_Delay(10); // 10 est une valeur correcte
        SDL_PumpEvents();    // Met à jour la table : 'const Uint8 *keyState = SDL_GetKeyboardState[NULL]'

        if (keyState[SDL_SCANCODE_DOWN]) {
	    playerMovY += 1;
        }
        if (keyState[SDL_SCANCODE_UP]) {
    	    playerMovY -= 1;   
        }                              
        if (keyState[SDL_SCANCODE_RIGHT]) { 
            playerMovX += 1;
        }
        if (keyState[SDL_SCANCODE_LEFT]) { 
       	    playerMovX -= 1;
        }
        if (keyState[SDL_SCANCODE_SPACE]) {
            Vaisseau.shoot(rocketLst);  //XXX Pourquoi pas de &rocketLst ?
        }

    Vaisseau.move(playerMovX, playerMovY);
    mapIncrementation( rocketLst, mysdl.getWidth(), mysdl.getHeight() );
    playerMovX = playerMovY = 0;

    }

    exit(EXIT_SUCCESS);
}
