#ifndef OBJECT_H
#define OBJECT_H

class Object
{
    protected:
    int           posx;
    int           posy;
    int        posxMin;
    int        posxMax;
    int        posyMin;
    int        posyMax;
    int          width;
    int         height;
    int         startx;
    int         starty;
    int     directionX;  //haut:    -1; bas:    +1;
    int     directionY;  //gauche:  -1; droite: +1;
    int          speed;
    int authorizedMove;


    public:
    int getx() const          { return posx;       }
    int gety() const          { return posy;       }
    int getPosyMin() const    { return posyMin;    }
    int getPosyMax() const    { return posyMax;    }
    int getWidth()  const     { return width;      }
    int getHeight() const     { return height;     }
    int getDirX() const       { return directionX; }
    int getDirY() const       { return directionY; }
    int getStartX() const     { return startx;     }
    int getStartY() const     { return starty;     }
    int getSpeed() const      { return speed;      }

};

#endif
