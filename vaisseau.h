#include <list>
#ifndef vaisseau_h
#define vaisseau_h
#include "object.h"
#include "rocket.h"

class vaisseau: public Object {

    int kindOf;     // PLAYER | HOSTILE
    int deltaX;
    int deltaY;
    int health;

    public:

    void setx(int x_) { posx = x_; }
    void sety(int y_) { posy = y_; }

    void setxMin(int xmin) { posxMin = xmin; }
    void setyMin(int ymin) { posyMin = ymin; }
    void setxMax(int xmax) { posxMax = xmax; }
    void setyMax(int ymax) { posyMax = ymax; }

    void delta(int w_, int y_);
    void resetDelta();

    int move();
    int shoot (std::list<rocket>& rocketLst);

    vaisseau(int, int, int);
    ~vaisseau();

};

#endif
