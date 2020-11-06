//
// Created by trykr on 23.10.2020.
//

#include "Player.h"

Player::Player(sf::Color color, const int weaponCount[WEAPONS_COUNT])
{
    this->color = color;
    for(auto & unit : units)
    {
        unit = new Unit("tux_from_linux.png", sf::Vector2f (100, 150), 3.f,
                        sf::Vector2u(3,9), 0.25, 100); //
    }
    sf::Texture* weaponTexture = new sf::Texture();
    weaponTexture->loadFromFile("RedPoint.png");
//    for (int i = 0; i < WEAPONS_COUNT; i++)
//    {
//        weaponVector.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Weapon()}, 10));
//    }
}

Player::~Player()
{

}

void Player::playerTurn()
{

}

Unit* Player::getUnits() {
    return *units;
}

void Player::setNextCurrentUnit()
{
    currentUnitID++;
    if (currentUnitID == UNIT_COUNTER)
        currentUnitID = 0;
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
