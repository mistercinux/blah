#include <iostream>
#include "vaisseau.h"
#include "rocket.h"

void rocket::init(vaisseau Vaisseau) {

  x = (Vaisseau.getx() + ((Vaisseau.x_size) / 2));
  y = (Vaisseau.gety());
  direction = Vaisseau.getdir();
  speed = ROCKET_SPEED;
  interval = ROCKET_INTERVAL;

  next = NULL;
}
