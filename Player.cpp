//
// Created by trykr on 23.10.2020.
//

#include "Player.h"

Player::Player(sf::Color color,sf::Font* font)
{
    this->color = color;
    for(int i = 0; i < UNIT_COUNTER; i++)
    {
        units[i] = new Unit("PenguinRed.png", sf::Vector2f (100, 150), 2.5,
                            sf::Vector2u(3,9), 0.25, 500, font, color);
    }
//    for (int i = 0; i < WEAPONS_COUNT; i++)
//    {
//        weaponVector.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Weapon()}, 10));
//    }
}

Player::~Player()
{
    for (int i = 0; i < UNIT_COUNTER; i++)
    {
        delete units[i];
    }
}

void Player::playerTurn()
{

}

Unit* Player::getUnit(int number) {
    return units[number];
}


Unit *Player::getCurrentUnit() {
    return units[currentUnitID];
}

unsigned int Player::getCurrentWeaponID() {
    return currentWeaponID;
}

void Player::setCurrentWeaponID(unsigned int newID)
{
    currentWeaponID = newID;
}

bool Player::getIsDefeated() {
    return isDefeated;
}

void Player::analiseSituation()
{
    bool isAnyoneAlive = false;
    for (int i = 0; i < UNIT_COUNTER; i++)
    {
        if (units[i]->getState() != UnitState::dead)
        {
            isAnyoneAlive = true;
        }
    }
    if (!isAnyoneAlive)
        isDefeated = true;
}
