#include <iostream>
#include "vaisseau.h"
#include "rocket.h"
#include "object.h"

void rocket::init(vaisseau Vaisseau) {

    width = 3;
    height = 8;
    posx = (Vaisseau.getx() + ((Vaisseau.getWidth()) / 2) - 1);
    posy = (Vaisseau.gety());
    starty = posy;
    startx = posx;
    directionY = Vaisseau.getDirY();
    speed = ROCKET_SPEED;
    interval = ROCKET_INTERVAL;

    next = NULL;
}

// Retourne 1 si l'interval entre 2 tirs est respecté et -1 si non.
int rocket::intervalCheck() {
  
  // Cette fonction posera des problèmes lorsque les autres vaisseaux vont tirer aussi si ils sont dans la même liste
  // Peut être faudra-t-il travailler avec 1 liste par vaisseau (liste de listes? :)
  
    int i;
  
    i = (posy - starty);
    
    if ((i*i) >= (interval*interval)) { return  1; }
    else { return -1; }
}
