#include "vaisseau.h"

vaisseau::vaisseau() {

  x_size = 40;
  y_size = 80;
  
  posx = 0; 
  posy = 0; 
  
  posx_min = 0;
  posx_max = 0;
  
  posy_min = 0;
  posy_max = 0;

  direction = 0; // PLAYER | COMPUTER (voir header)
}


vaisseau::~vaisseau() { }

void vaisseau::movex(int delta) {
  if (delta > 0) {
    if ((posx + delta) <= posx_max)
      posx += delta;
    }
  else if (delta < 0)
    if((posx + delta) >= posx_min)
      posx += delta;	  
}

void vaisseau::movey(int delta) {
  if (delta > 0) {
    if ((posy + delta) <= posy_max) {
      posy += delta;
    }
  }
  else if (delta < 0)
    if((posy + delta) >= posy_min)
      posy += delta;
}  


  
