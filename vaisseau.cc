#include "vaisseau.h"
#include "object.h"

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
            if ((posx + x_) <= posxMax) { posx += x_; }
        }
        else if (x_ < 0)
        {
            if((posx + x_) >= posxMin) { posx += x_; }	  
        }

        if (y_ > 0) 
        {
            if ((posy + y_) <= posyMax) { posy += y_; }
        }
        else if (y_ < 0) 
        {
            if((posy + y_) >= posyMin) { posy += y_; }  
        }
  }
}

void vaisseau::start(int player_, int screenW, int screenH)
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

