#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"

#define ROCKET_SPEED 20
#define ROCKET_INTERVAL 100

class rocket {

  int interval;   // Distance minimum entre 2 coups

 public:

    

  int getstart() { return starty; }
  
  void set

  void move() { y += (speed * direction); }

  int intervalCheck();
  
  rocket* next;

  void init (vaisseau Vaisseau);

};

#endif
