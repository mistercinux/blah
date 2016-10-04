#ifndef ROCKET_H
#define ROCKET_H
#include "object.h"

#define ROCKET_SPEED 20
#define ROCKET_INTERVAL 100

class rocket: public Object {

    int interval;   // Distance minimum entre 2 coups

    public:    

    void move() { posy += (speed * directionY); }
    int intervalCheck();
    rocket* next;
    void init (vaisseau Vaisseau);

};

#endif
