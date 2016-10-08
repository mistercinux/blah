#include <list>
#ifndef vaisseau_h
#define vaisseau_h
#include "object.h"
#include "rocket.h"

#define PLAYER   1 
#define HOSTILE  2
#define UP      -1
#define DOWN     1


class vaisseau: public Object {
  
    int kindOf;     // PLAYER | HOSTILE
    
    public:
  
    void setx(int x_) { posx = x_; }
    void sety(int y_) { posy = y_; }

    void setxMin(int xmin) { posxMin = xmin; }
    void setyMin(int ymin) { posyMin = ymin; }
    void setxMax(int xmax) { posxMax = xmax; }
    void setyMax(int ymax) { posyMax = ymax; }
  
    void move(int x_, int y_);
    void setDirY(int dirx) { directionX = dirx; } // PLAYER ou COMPUTER
    //void start (int player_, int screenW_, int screenH_);
    int  shoot (std::list<rocket>& rocketLst);

    vaisseau(int, int, int);
    ~vaisseau();
  
};

#endif
