#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"

#define ROCKET_SPEED 15
#define ROCKET_INTERVAL 100

class rocket: public Object {

    int interval;   // Distance minimum entre 2 coups

    public:

    int getstart() { return starty; }
    int  intervalCheck();
  
    void move() { posy += (speed * directionY); }
    void init (int x_, int y_, int shipWidth, int directionY_);

    rocket();
    rocket(int, int, int, int);

};

#endif
