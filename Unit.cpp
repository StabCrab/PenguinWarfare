//
// Created by trykr on 12.10.2020.
//

#include "Unit.h"

Unit::Unit(const std::string& texturePath,sf::Vector2f sizeUnit, float mass,
           sf::Vector2u imageCount, float switchTime, float speed, sf::Font* font, sf::Color color)
           : Entity(texturePath, sizeUnit, mass),
           animation(getBody().getTexture()->getSize(), imageCount, switchTime),
           speed(speed)
{
    state = UnitState::idle;
    isFaceRight = true;
    info.setFont(*font);
    info.setFillColor(color);
    info.setString(std::to_string(health));
    info.setPosition(getTopCoordinates());
    info.setOrigin(25.f,20.f);
}

Unit::~Unit()
{

}

void Unit::idle(float deltaTime)
{
    if (state != UnitState::dead)
    {
        state = UnitState::idle;
        clearMomentum();
    }
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
    animation.Update(static_cast<unsigned int>(state) % 9, deltaTime, isFaceRight);
    setTextureRect(animation.getUVRect());
    drawBody(window);
    info.setPosition(getTopCoordinates());
    if (state != UnitState::dead)
        window.draw(info);
}

void Unit::setIsFaceRight(bool isFaceRight)
{
    this->isFaceRight = isFaceRight;
}

bool Unit::getIsFaceRight() {
    return isFaceRight;
}

void Unit::takeDamage(sf::Vector2f blowImpulse, unsigned int damage)
{
    health -= damage;
    addVectorToMomentum(blowImpulse);
    info.setString(std::to_string(health));
    if (health < 0)
        state = UnitState::dead;
}

UnitState Unit::getState() {
    return state;
}

void Unit::makeUnitOutOfBounds()
{
    state = UnitState::dead;
    isOutOfBounds = true;
    setPosition(sf::Vector2f(100,100));
}

bool Unit::getIsOutOfBounds() {
    return isOutOfBounds;
}

void Unit::jumpForward()
{
    sf::Vector2f movement;
    if (isFaceRight)
        movement = sf::Vector2f(15, -8);
    else
        movement = sf::Vector2f(-15, -8);
    addVectorToMomentum(movement);
}

void Unit::jumpBackwards()
{
    sf::Vector2f movement;
    if (isFaceRight)
        movement = sf::Vector2f(-8, -15);
    else
        movement = sf::Vector2f(8, -15);
    addVectorToMomentum(movement);
}


