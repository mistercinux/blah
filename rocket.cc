#include <iostream>
#include "vaisseau.h"
#include "rocket.h"
#include "object.h"

rocket::rocket(int x_, int y_, int shipWidth_, int directionY_) {

    width = 4;	// Largeurt de roquette
    height = 8; // Hauteur de roquette
    posx = (x_ + (shipWidth_ / 2) - 1);
    posy = y_;
    starty = posy;
    startx = posx;
    directionY = directionY_; 
    speed = ROCKET_SPEED;
    interval = ROCKET_INTERVAL;
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

