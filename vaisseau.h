#ifndef vaisseau_h
#define vaisseau_h

#define PLAYER    -1
#define COMPUTER   1

class vaisseau {
  
  int posx;
  int posy;
  int posx_min;
  int posx_max;
  int posy_min;
  int posy_max;
  int direction; // pour le joueur: -1 (vers le haut), pour les autres +1 (vers le bas)
  
public:
  
  int x_size;
  int y_size;

  int getx( )  { return posx; }
  int gety( )  { return posy; }

  void setx(int x) { posx = x; }
  void sety(int y) { posy = y; }

  void setx_max(int xmax) { posx_max = xmax; }
  void sety_max(int ymax) { posy_max = ymax; }
  
  void movex(int delta);
  void movey(int delta);

  int getdir()  { return direction; }
  void setdir(int dir) { direction = dir; } // PLAYER ou COMPUTER

  vaisseau();
  ~vaisseau();
  
};

#endif
