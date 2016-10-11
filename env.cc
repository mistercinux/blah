#include <iostream> // pour debug..
#include <random>
#include "env.h"
#include "rocket.h"
#include "vaisseau.h"
#include <list>

env::env()
{
    maxHostiles         =   3;  // quantité MAX d'ennemis
    authorizedHostiles  =   2;  // Quantité d'ennemis a créer (entre 0 et maxHostileShips inclus)
    lastGen             =   0;
    genInterval         =  50;  // nombre de boucles avant nouvelles générations

}

env::~env() { }


void env::genHostile()
{
    std::cout << "génération d'un vaisseau ennemi..." << std::endl;
    shipLst.push_back( vaisseau(hostile, screenW, screenH) );

    lastGen = 0;

    std::random_device generator;
    std::uniform_int_distribution<int> distrib(1,maxHostiles);
    authorizedHostiles = distrib(generator);

}
int env::colisionCheck(rocket& rocket_, vaisseau& vaisseau_)
{
    /*if (rocket_.getDirY() == vaisseau_.getDirY()) { return 0; }

    for(int i=0; i < vaisseau_.getWidth(); ++i)
    {
        if (rocket_.getx() == (vaisseau_.getx()+i))
        {
            std::cout << vaisseau_.getWidth() << " :: Vaisseau dans la ligne de mirE..." << std::endl;
        }
        else { std::cout << "HORS DE LIGNE DE MIRE..." << std::endl; return 0; }
    }

    int yShip = 0;

    if ( vaisseau_.getDirY() == 1 ) // Hostile = 1, player = -1;
        { yShip = (vaisseau_.gety() + vaisseau_.getHeight()); }
    else
        { yShip = vaisseau_.gety(); }

    for (int i=0; i < 40; ++i)
    {
        if (rocket_.gety() != (yShip + (i * vaisseau_.getDirY())))
        {
            std::cout << "SHOOOOOOOOOOOOOOOOTTTTTTTTTTTTTTEEEEEEEEEEEEEEEDDDDDDDDDDDDDDDDDDDDD..." << std::endl;
        }
    }

    return 0;
*/
}

int env::manager()
{

    // *** Gestion de la liste de roquettes *** //
    std::list<rocket>::iterator rocketIt;
    std::list<vaisseau>::iterator shipIt;

    if(rocketLst.size() != 0)
    {
        for(rocketIt = rocketLst.begin(); rocketIt != rocketLst.end(); ++rocketIt)
        {
            rocketIt->move();
            if ((rocketIt->gety() <= rocketIt->getPosyMin()) | (rocketIt->gety() >= rocketIt->getPosyMax()))
            {
                rocketIt = rocketLst.erase(rocketIt);
            }

            for( shipIt = shipLst.begin(); shipIt != shipLst.end(); ++shipIt)
            {
                for(int i=0; i < shipIt->getWidth(); ++i)
                {
                    if (rocketIt->getx() == (shipIt->getx()+i))
                    {
                        // REMPLACER PAR cosisionCheck
                        //std::cout << "Vaisseau dans la ligne de mire..." << std::endl;
                        colisionCheck(*rocketIt, *shipIt);
                    }
                }
            }
        }
    }

    // *** Gestion de la liste des vaisseaux ennemis *** //
    ++lastGen;
    if(shipLst.size() < authorizedHostiles)
    {
        if(lastGen >= genInterval) { genHostile(); }
    }

    if(shipLst.size() != 0)
    {

        for(shipIt = shipLst.begin(); shipIt != shipLst.end(); ++shipIt)
        {

           if (shipIt->move() == -1)
            {
                // std::cout << "Fin de course: Y =  " << shipIt->gety() << std::endl;
                shipIt = shipLst.erase(shipIt);
            }

        }

    }


    return 0;

}

