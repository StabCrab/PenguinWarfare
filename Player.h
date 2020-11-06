//
// Created by trykr on 23.10.2020.
//

#ifndef PENGUINWARFARE_PLAYER_H
#define PENGUINWARFARE_PLAYER_H
#include "Unit.h"
#include "Weapon.h"

#define UNIT_COUNTER 1
class Player
{
private:
    Unit* units[UNIT_COUNTER];
    sf::Color color;
    unsigned int weaponsArray[WEAPONS_COUNT];
    unsigned int currentWeaponID = 0;
    unsigned int currentUnitID = 0;
public:
    Player(sf::Color color, const int weaponCount[WEAPONS_COUNT]);
    ~Player();
    void playerTurn();
    Unit* getUnits();
    void setNextCurrentUnit();
    Unit* getCurrentUnit();
    unsigned int getCurrentWeaponID();
    void setCurrentWeaponID(unsigned int newID);
};


#endif //PENGUINWARFARE_PLAYER_H
