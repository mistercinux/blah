#ifndef ROCKET_H
#define ROCKET_H

#define ROCKET_SPEED 10
#define ROCKET_INTERVAL 50

class rocket {

  int x;
  int y;          
  int direction;  // Vers le haut: -1 et vers le bas +1
  int speed;      // Vitesse de déplacement en pixels/affichage
  int interval;   // Distance minimum entre 2 coups

 public:

  int getx() { return x; }
  int gety() { return y; }
  
  void setx(int posx)  { x = posx; }
  void sety(int posy)  { y = posy; }

  void setdir(int dir) { direction = dir; }

  int move();
  
  rocket* next;

  void init (vaisseau Vaisseau);

};

#endif
