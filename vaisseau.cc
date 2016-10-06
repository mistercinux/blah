#include <list>
#include "vaisseau.h"
#include "object.h"
#include "rocket.h"

vaisseau::vaisseau() {

    width   = 40;
    height  = 80;
    posx    =  0; 
    posy    =  0; 
    posxMin =  0;
    posxMax =  0;
    posyMin =  0;
    posyMax =  0;


    directionY      = -1; // PLAYER | COMPUTER (voir header)
    player          =  1;
    authorizedMove  =  1;
    
    speed = 10;


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

void vaisseau::start(int player_, int screenW, int screenH) // player_ = 1 si c'est le joueur; 0 sinon;
{
    if (player_ == 1)    
    {
        posx = ((screenW / 2) - (width / 2));
        posy = (screenH - (2 * height));
        posxMax = (screenW - width);
        posyMax = (screenH - height);
        directionY = -1;
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
     
    //rocketLst.push_back(rocketLst.back());
    rocketLst.push_back(rocketLst.front());

    ++rocketIt;
    rocketIt->init(posx, posy, width, directionY);
    return 1;
}
