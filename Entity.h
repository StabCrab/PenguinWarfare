//
// Created by trykr on 15.10.2020.
//

#ifndef WORMSPROTOTYPE_ENTITY_H
#define WORMSPROTOTYPE_ENTITY_H
#include "SFML/Graphics.hpp"

class Entity
{
private:
    sf::RectangleShape body;
    const float mass;
    sf::Vector2f momentum = sf::Vector2f(0.f,0.f);
    sf::Vector2f pseudoCoordinates;
    bool isOutOfBounds = false;

public:
    Entity(const std::string& texturePath,sf::Vector2f size ,float mass);
    Entity(sf::Texture* texture, sf::Vector2f size, float mass);
    ~Entity();

    sf::Vector2f getPosition();
    sf::Vector2f getTopCoordinates();
    sf::Vector2f getBottomCoordinates();
    sf::Vector2f getLeftBottomCoordinates();
    sf::Vector2f getRightBottomCoordinates();
    sf::Vector2f getRightCoordinates();
    sf::Vector2f getLeftCoordinates();

    void fall(float deltaTime, const float gravity);

    void pushLeftFromTexture(float deltaTime);
    void pushRightFromTexture(float deltaTime);
    void pushUpFromTexture(float deltaTime);

    void addVectorToMomentum(sf::Vector2f movement);
    sf::Vector2f getMomentum();
    void clearMomentum();
    void moveBody();

    sf::RectangleShape getBody();
    void move(sf::Vector2f movementVector);
    void setTextureRect(sf::IntRect textureRect);
    float getMass();
    void setTexture(sf::Texture* texture);
    void setPosition(sf::Vector2f position);
    void drawBody(sf::RenderWindow& window);
    void rotate(float angle);
    void setRotation(float angle);
    void reverse();
    sf::Vector2f getPseudoCoordinates();
    void frictionForce();
    bool getIsOutOfBounds();
    void setOutOfBounds(bool newIsOutOfBounds);
    void nullifyMomentum();
};


#endif //WORMSPROTOTYPE_ENTITY_H
