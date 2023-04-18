//
// Created by trykr on 23.10.2020.
//

#ifndef PENGUINWARFARE_PLAYER_H
#define PENGUINWARFARE_PLAYER_H
#include "Unit.h"

#define UNIT_COUNTER 1
class Player
{
private:
    Unit* units[UNIT_COUNTER];
    sf::Color color;
    unsigned int currentWeaponID = 0;
    unsigned int currentUnitID = 0;
    short int aliveUnitsCount = UNIT_COUNTER;
    bool isDefeated = false;
public:
    Player(sf::Color color, sf::Font* font);
    ~Player();
    void playerTurn();
    Unit* getUnit(int number);
    Unit* getCurrentUnit();
    unsigned int getCurrentWeaponID();
    void setCurrentWeaponID(unsigned int newID);
    bool getIsDefeated();
    void analiseSituation();
};


#endif //PENGUINWARFARE_PLAYER_H
