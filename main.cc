#include <iostream>	
#include <SDL2/SDL.h>       // Les fonctions commencent par SDL
#include <SDL2/SDL_image.h> // Les fonctions commencent par IMG
#include <list>
#include "vaisseau.h"
#include "rocket.h"
#include "gestion_sdl.h"
#include "env.h"



/*****************************
 *          M A I N          *
 *****************************/

int main()
{
    std::list<rocket>::iterator   rocketIt;
    std::list<vaisseau>::iterator hostileIt;
    gestion_sdl                   mysdl;
    env                           level;

    mysdl.init( level.backgroung_img(), level.player_img(), level.hostile_img(), level.greenRocket_img() );

    level.setScreen(mysdl.getWidth(), mysdl.getHeight());
    vaisseau    Vaisseau( level.player, mysdl.getWidth(), mysdl.getHeight() );

    /* ajout manuel d'un ennemi pout test
    std::cout << "toto?" << hostileLst.size() <<std::endl;
    hostileLst.push_back( vaisseau(level.hostile, mysdl.getWidth(), mysdl.getHeight()) );
    std::cout << "toto?" << hostileLst.size() <<std::endl;
    hostileIt = hostileLst.begin();
    std::cout << "toto?" << hostileIt->gety() <<std::endl;
*/
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    // Boucle principale //
    /*********************/

    std::cout << "Appuyez sur la touche ESC pour quitter..." << std::endl;

    while (!keyState[SDL_SCANCODE_ESCAPE]) {

        mysdl.renderClear();
        // Affichage du background
        SDL_RenderCopy(mysdl.mainRenderer__, mysdl.backgroundTex__, NULL, NULL);

        //Affichage du vaisseau principal
        mysdl.renderTexture(mysdl.playerTex__, mysdl.mainRenderer__, Vaisseau.getx(), Vaisseau.gety());

        // Affichage des vaisseaux ennemis si il y en a dans la liste
        if (level.shipLst.size() > 0)
        {
            for ( hostileIt = level.shipLst.begin(); hostileIt != level.shipLst.end(); ++hostileIt)
            {
            mysdl.renderTexture(mysdl.hostileTex__, mysdl.mainRenderer__, hostileIt->getx(), hostileIt->gety());
            }
        }

        //Affichage des roquettes si il y en a dans la liste
        if(level.rocketLst.size() > 0)
        {
            for(rocketIt = level.rocketLst.begin(); rocketIt != level.rocketLst.end(); ++rocketIt)
            {
                mysdl.renderTexture(mysdl.greenRocketTex__, mysdl.mainRenderer__, rocketIt->getx(), rocketIt->gety(), rocketIt->getWidth(), rocketIt->getHeight());
            }
        }

        SDL_RenderPresent(mysdl.mainRenderer__);
        SDL_Delay(50); // 10 est une valeur correcte

        // Gestion des évènements associés au clavier
        SDL_PumpEvents();

        if (keyState[SDL_SCANCODE_DOWN]) {
            Vaisseau.delta(0, -1);
        }
        if (keyState[SDL_SCANCODE_UP]) {
            Vaisseau.delta(0, 1);
        }
        if (keyState[SDL_SCANCODE_RIGHT]) {
            Vaisseau.delta(1, 0);
        }
        if (keyState[SDL_SCANCODE_LEFT]) {
            Vaisseau.delta(-1, 0);
        }
        if (keyState[SDL_SCANCODE_SPACE]) {
            Vaisseau.shoot(level.rocketLst);
        }

        Vaisseau.move();
        level.manager();

    }

    exit(EXIT_SUCCESS);
}
