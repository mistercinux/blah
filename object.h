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
    int getx()      { return posx;       }
    int gety()      { return posy;       }
    int getWidth()  { return width;      }
    int getHeight() { return height;     }
    int getDirX()   { return directionX; }
    int getDirY()   { return directionY; }
    int getStartX() { return startx;     }
    int getStartY() { return starty;     }
    int getSpeed()  { return speed;      }

};

#endif
