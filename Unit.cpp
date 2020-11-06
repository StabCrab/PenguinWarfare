//
// Created by trykr on 12.10.2020.
//

#include "Unit.h"

Unit::Unit(std::string texturePath,sf::Vector2f sizeUnit, float mass,
           sf::Vector2u imageCount, float switchTime, float speed)
           : Entity(texturePath, sizeUnit, mass),
           animation(getBody().getTexture()->getSize(), imageCount, switchTime),
           speed(speed)
{
    state = UnitState::idle;
    isFaceRight = true;
}

Unit::~Unit()
{

}

void Unit::idle(float deltaTime)
{
    state = UnitState::idle;
    clearMomentum();
}

void Unit::walk(float deltaTime, bool isGoingRight)
{
    sf::Vector2f movement(0,0);
    if(isGoingRight)
    {
        isFaceRight = true;
        movement.x += speed * deltaTime;
    }
    else
    {
        isFaceRight = false;
        movement.x -= speed * deltaTime;
    }
    clearMomentum();
    addVectorToMomentum(movement);
    state = UnitState::walking;

}



void Unit::draw(sf::RenderWindow& window, float deltaTime)
{
    animation.Update(static_cast<unsigned int>(state), deltaTime, isFaceRight);
    setTextureRect(animation.uvRect);
    drawBody(window);
}

void Unit::setIsFaceRight(bool isFaceRight)
{
    this->isFaceRight = isFaceRight;
}

bool Unit::getIsFaceRight() {
    return isFaceRight;
}


