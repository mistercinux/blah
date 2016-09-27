#include <iostream>
#include "vaisseau.h"
#include "rocket.h"

void rocket::init(vaisseau Vaisseau) {

  sizex = 3;
  sizey = 8;
  x = (Vaisseau.getx() + ((Vaisseau.x_size) / 2) - 1);
  y = (Vaisseau.gety());
  starty = y;
  direction = Vaisseau.getdir();
  speed = ROCKET_SPEED;
  interval = ROCKET_INTERVAL;

  next = NULL;
}

// Retourne 1 si l'interval entre 2 tirs est respecté et -1 si non.
int rocket::intervalCheck() {
  
  // Cette fonction posera des problèmes lorsque les autres vaisseaux vont tirer aussi si ils sont dans la même liste
  // Peut être faudra-t-il travailler avec 1 liste par vaisseau (liste de listes? :)
  
  int i;
  
  i = (y - starty);
  if ((i*i) >= (interval*interval)) {
    return  1;
  }
  else  {
    return -1; }
}
