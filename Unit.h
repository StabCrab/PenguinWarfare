//
// Created by trykr on 12.10.2020.
//

#ifndef WORMSPROTOTYPE_UNIT_H
#define WORMSPROTOTYPE_UNIT_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Entity.h"
#include "Weapon.h"
enum class UnitState
{
    idle = 0,
    walking,
    jumping,
    gettingWounded
};
class Unit : public Entity
{
public:
    Unit(std::string texturePath, sf::Vector2f sizeUnit, float mass,
         sf::Vector2u imageCount, float switchTime, float speed);
    ~Unit();
    void idle(float deltaTime);
    void walk(float deltaTime, bool isGoingRight);
    void draw(sf::RenderWindow& window, float deltaTime);
    bool getIsFaceRight();
    void setIsFaceRight(bool isFaceRight);
private:
    Animation animation;
    float speed;
    bool isFaceRight;
    UnitState state;
    Weapon* weaponInHands;
};


#endif //WORMSPROTOTYPE_UNIT_H
