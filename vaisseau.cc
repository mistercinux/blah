#include <list>
#include "vaisseau.h"
#include "object.h"
#include "rocket.h"

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
    kindOf          =  kindOf_; 
    authorizedMove  =        1;

    switch (kindOf_)
    {    
        case PLAYER:   
            directionY  = UP;   // PLAYER | COMPUTER (voir header)
            speed       = 10;
            width       = 40;
            height      = 80;
            posx        = ((screenW / 2) - (width / 2));
            posy        = (screenH - (2 * height));
            posxMax     = (screenW - width);
            posyMax     = (screenH - height);
            break;

        case HOSTILE:
            directionY  = DOWN; 
            speed       = 10;
            width       = 40;
            height      = 80;
            break;

    }
}


vaisseau::~vaisseau() { }

void vaisseau::move(int x_, int y_) {

    if (authorizedMove)
    {
        if (x_ > 0) 
        {
            if ((posx + x_) <= posxMax) { posx += (speed * x_); }
        }
        else if (x_ < 0)
        {
            if ((posx + x_) >= posxMin) { posx += (speed * x_); }	  
        }

        if (y_ > 0) 
        {
            if ((posy + y_) <= posyMax) { posy += (speed * y_); }
        }
        else if (y_ < 0) 
        {
            if ((posy + y_) >= posyMin) { posy += (speed * y_); }  
        }
  }
}


/*
void vaisseau::start(int who_, int screenW, int screenH) // Who = PLAYER | HOSTILE
{
    if (who_ == PLAYER)    
    {
        posx = ((screenW / 2) - (width / 2));
        posy = (screenH - (2 * height));
        posxMax = (screenW - width);
        posyMax = (screenH - height);
        directionY = -1;
    }


}
*/



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
