#include <list>
#include "vaisseau.h"
#include "object.h"
#include "rocket.h"
#include <iostream> // pour tests cout...

vaisseau::vaisseau(int kindOf_, int screenW, int screenH) {

    // Il est pénible de devoir passer en args les dimentions de la fenetre
    // à plusieurs méthodes de différentes class.
    // Trouver une solution efficace !!! :)

    posx            =        0;
    posy            =        0;
    posxMin         =        0;
    posxMax         =        0;
    posyMin         =        0;
    posyMax         =        0;
    kindOf          =  kindOf_; // Peut prendre les valeurs : 1 (= player); 2 (= hostile);
    authorizedMove  =        1;
    deltaX          =        0;
    deltaY          =        0;
    directionX      =        1;

    switch (kindOf_)
    {
        case 1:                 // 1 = Player
            directionY  = -1;   // Up
            speed       = 10;
            width       = 40;
            height      = 80;
            posx        = ((screenW / 2) - (width / 2));
            posy        = (screenH - (2 * height));
            posxMax     = (screenW - width);
            posyMax     = (screenH - height);
            break;

        case 2:                 // 2 = Hostile
            directionY  =  1;   // Down
            speed       =  5;
            width       = 40;
            height      = 80;
            posyMax = screenH + speed;
            posyMin = 0 - (height + speed);
            posxMax = screenW - width;
            posy    = posyMin + 1;
            posx    = 100;
            deltaY = (speed * directionY);
            break;

    }
}


vaisseau::~vaisseau() { std::cout << "vaisseau détruit" << std::endl; }

void vaisseau::delta(int x_, int y_)
{
    deltaX += ( speed * directionX * x_ );
    deltaY += ( speed * directionY * y_ );
}

void vaisseau::resetDelta()
{
    deltaX = 0;
    deltaY = 0;
}

int vaisseau::move() {

    int err=0;

    if (authorizedMove)
    {

        if ( (posy + deltaY) <= posyMax )
        {
            if ( (posy + deltaY) >= posyMin )
            {
                posy += deltaY;
                }
        }
        else { err = 1; }


        if ( (posx + deltaX) <= posxMax )
        {
            if ( (posx + deltaX) >= posxMin )
            {
                posx += deltaX;
            }
        }
        else { err = 1; }

        std::cout<<"kindOf / posy / ymax --- " << kindOf << " "<< posy <<" "<< posyMax <<" "<< std::endl;

        if ( kindOf == 1 )  { resetDelta();  }
        if (err == 1)       { return -1;        }
        return 1;
    }
}


int vaisseau::shoot(std::list<rocket>& rocketLst)
{

    std::list<rocket>::iterator rocketIt;

    rocketIt = rocketLst.end();
    --rocketIt;

    if(rocketLst.size() > 0)
    {
        if (rocketIt->intervalCheck() == -1) { return 0; }
    }

    rocketLst.push_back(rocket( posx, posy, width, directionY ));

    return 1;
}
