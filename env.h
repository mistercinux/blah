#ifndef	ENV_H
#define ENV_H

#include <list>
#include <string>
#include "rocket.h"
#include "vaisseau.h"

class env
{
     // paramètres d'affichage
    const std::string bgPath = "images/fond.png";
    const std::string hostilePath = "images/hostile.png";
    const std::string playerPath = "images/player.png";
    const std::string greenRocketPath = "images/laser_vert.png";
    int screenW;
    int screenH;

    // Paramètres à passer pour la génération de nouveaux vaisseaux
    unsigned int maxHostiles;         // Quantité d'ennemis max (en fonction du level)
    unsigned int AliveHostiles;       // Quantité d'ennemis actuels
    unsigned int authorizedHostiles;  // Quantité d'ennemis a créer (entre 0 et maxHostileShips inclus)
    unsigned int genInterval;         // nombre de boucles avant nouvelles générations
    unsigned int lastGen;             // incrémenté à chaque tour et remis à 0 lors d'une génération

    public:
    int player        = 1;
    int hostile       = 2;
    int greenRocket   = 3;
    int redRocket     = 4;

    std::list<rocket>   rocketLst;
    std::list<vaisseau>  shipLst;

    int manager();

    std::string backgroung_img() const    { return bgPath.c_str();          }
    std::string hostile_img() const       { return hostilePath.c_str();     }
    std::string player_img() const        { return playerPath.c_str();      }
    std::string greenRocket_img() const   { return greenRocketPath.c_str(); }

    void setScreen(int x_, int y_) {screenW = x_; screenH = y_; }
    void genHostile();

    env();
    ~env();
};

#endif
