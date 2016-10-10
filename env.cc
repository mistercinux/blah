#include <iostream> // pour debug..
#include "env.h"
#include "rocket.h"
#include "vaisseau.h"
#include <list>

env::env()
{
    maxHostiles         =   1;
    AliveHostiles       =   0;  // Quantité d'ennemis actuels
    authorizedHostiles  =   1;  // Quantité d'ennemis a créer (entre 0 et maxHostileShips inclus)
    lastGen             =   0;
    genInterval         = 150;  // nombre de boucles avant nouvelles générations



}

env::~env() { }


void env::genHostile()
{
    std::cout << "génération d'un vaisseau ennemi..." << std::endl;
    shipLst.push_back( vaisseau(hostile, screenW, screenH) );
    lastGen = 0;
}


int env::manager()
{


    // *** Gestion de la liste de roquettes *** //
    std::list<rocket>::iterator rocketIt;
    if(rocketLst.size() != 0)
    {
        for(rocketIt = rocketLst.begin(); rocketIt != rocketLst.end(); ++rocketIt)
        {
            rocketIt->move();
            if ((rocketIt->gety() <= rocketIt->getPosyMin()) | (rocketIt->gety() >= rocketIt->getPosyMax()))
            {
                rocketIt = rocketLst.erase(rocketIt);
            }
        }
    }

    // *** Gestion de la liste des vaisseaux ennemis *** //
    ++lastGen;
    if(shipLst.size() < authorizedHostiles)
    {
        if(lastGen == genInterval) { genHostile(); }
    }

    if(shipLst.size() != 0)
    {
        std::list<vaisseau>::iterator shipIt;

        for(shipIt = shipLst.begin(); shipIt != shipLst.end(); ++shipIt)
        {

           if (shipIt->move() == -1)
            {
                std::cout << "Fin de course: Y =  " << shipIt->gety() << std::endl;
                shipIt = shipLst.erase(shipIt);
            }

        }

    }


    return 0;

}

