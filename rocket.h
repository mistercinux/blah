#ifndef ROCKET_H
#define ROCKET_H

#define ROCKET_SPEED 20
#define ROCKET_INTERVAL 100

class rocket {

  int sizex; // 1 par defaut dans rocket.cc
  int sizey; // 3 par defaut dans rocket.cc
  int starty;
  int x;
  int y;          
  int direction;  // Vers le haut: -1 et vers le bas +1
  int speed;      // Vitesse de déplacement en pixels/affichage
  int interval;   // Distance minimum entre 2 coups

 public:

  int getx() { return x; }
  int gety() { return y; }

  int getsizex() { return sizex; }
  int getsizey() { return sizey; }

  int getstart() { return starty; }
  
  void setx(int posx)  { x = posx; }
  void sety(int posy)  { y = posy; }

  void setdir(int dir) { direction = dir; }

  void move() { y += (speed * direction); }

  int intervalCheck();
  
  rocket* next;

  void init (vaisseau Vaisseau);

};

#endif
