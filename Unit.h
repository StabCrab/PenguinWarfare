//
// Created by trykr on 12.10.2020.
//

#ifndef WORMSPROTOTYPE_UNIT_H
#define WORMSPROTOTYPE_UNIT_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Entity.h"
#include "Weapon.h"
#include "string.h"
enum class UnitState
{
    idle = 0,
    walking = 1,
    jumping = 2,
    gettingDamage = 3,
    dead = 8,
    outOfBounds
};
class Unit : public Entity
{
public:
    Unit(const std::string& texturePath, sf::Vector2f sizeUnit, float mass,
         sf::Vector2u imageCount, float switchTime, float speed, sf::Font* font, sf::Color color);
    ~Unit();
    void idle(float deltaTime);
    void walk(float deltaTime, bool isGoingRight);
    void draw(sf::RenderWindow& window, float deltaTime);
    bool getIsFaceRight();
    void setIsFaceRight(bool isFaceRight);
    void takeDamage(sf::Vector2f blowImpulse, unsigned int damage);
    UnitState getState();
    void makeUnitOutOfBounds();
    bool getIsOutOfBounds();
private:
    bool isOutOfBounds = false;
    int health = 100;
    sf::Text info;
    Animation animation;
    float speed;
    bool isFaceRight;
    UnitState state;
    Weapon* weaponInHands;
};


#endif //WORMSPROTOTYPE_UNIT_H
