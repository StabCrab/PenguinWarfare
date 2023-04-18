//
// Created by trykr on 12.10.2020.
//

#ifndef WORMSPROTOTYPE_UNIT_H
#define WORMSPROTOTYPE_UNIT_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Entity.h"
#include "string.h"

enum class UnitState
{
    idle = 0,
    walking = 1,
    jumping = 2,
    gettingDamage = 3,
    dead = 8,
    falling,
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
    UnitState getState();
    void makeUnitOutOfBounds();
    bool getIsOutOfBounds();
    void jumpForward(float deltaTime);
    void jumpBackwards(float deltaTime);
    sf::Vector2f open();
    bool getHasKey();
    bool giveKey();

    void goToChest();
    void goToDoor();
    void stopGoingToChest();
    void stopGoingToDoor();

    bool getGoingToChest();
    bool getGoingToDoor();
private:
    bool isOutOfBounds = false;
    Animation animation;
    float speed;
    bool isFaceRight;
    UnitState state;
    sf::Text coords;
    bool hasKey = false;

    bool isGoingToChest = false;
    bool isGoingToDoor = false;
};


#endif //WORMSPROTOTYPE_UNIT_H
