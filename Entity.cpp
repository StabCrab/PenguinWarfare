//
// Created by trykr on 15.10.2020.
//

#include "Entity.h"

Entity::Entity(const std::string& texturePath,sf::Vector2f size ,float mass)
: mass(mass)
{
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.f);
    auto* texture = new sf::Texture;
    texture->loadFromFile(texturePath);
    texture->setSmooth(true);
    body.setTexture(texture);
}

Entity::Entity(sf::Texture* texture, sf::Vector2f size, float mass) : mass(mass)
{
    body.setSize(size);
    body.setOrigin(body.getSize() / 2.f);
    texture->setSmooth(true);
    body.setTexture(texture);
}

Entity::~Entity()
{

}

sf::RectangleShape Entity::getBody()
{
    return body;
}

void Entity::move(sf::Vector2f movementVector)
{
    body.move(movementVector);
}

void Entity::setTextureRect(sf::IntRect textureRect)
{
    body.setTextureRect(textureRect);
}

float Entity::getMass() {
    return mass;
}

void Entity::drawBody(sf::RenderWindow& window)
{
    window.draw(body);
}

void Entity::setPosition(sf::Vector2f position)
{
    body.setPosition(position);
}

sf::Vector2f Entity::getPosition()
{
    return body.getPosition();
}

sf::Vector2f Entity::getTopCoordinates()
{
    return sf::Vector2f (body.getPosition().x,
                         body.getPosition().y - (body.getSize().y / 2.f) + 5);
}

sf::Vector2f Entity::getBottomCoordinates()
{
    return sf::Vector2f (body.getPosition().x,
                         body.getPosition().y + (body.getSize().y / 2.f) - 5);
}

sf::Vector2f Entity::getLeftBottomCoordinates()
{
    return sf::Vector2f (body.getPosition().x - (body.getSize().x / 2.f) + 30,
                         body.getPosition().y + (body.getSize().y / 2.f) - 5);
}

sf::Vector2f Entity::getRightBottomCoordinates()
{
    return sf::Vector2f (body.getPosition().x + (body.getSize().x / 2.f) - 30,
                         body.getPosition().y + (body.getSize().y / 2.f) - 5);
}

sf::Vector2f Entity::getRightCoordinates()
{
    return sf::Vector2f (body.getPosition().x + (body.getSize().x / 2.f + 30),
                         body.getPosition().y);
}

sf::Vector2f Entity::getLeftCoordinates() {
    return sf::Vector2f (body.getPosition().x - (body.getSize().x / 2.f - 30),
                         body.getPosition().y);
}

void Entity::fall(float deltaTime, const float gravity)
{
    sf::Vector2f movement(0,0);
    movement.y += gravity * mass * deltaTime;
    addVectorToMomentum(movement);
}

void Entity::pushUpFromTexture(float deltaTime)
{
    sf::Vector2f movement(0,0);
    movement.y -= deltaTime;
    move(movement);
}

void Entity::clearMomentum()
{
    momentum.x = 0;
    momentum.y = 0;
}

void Entity::moveBody()
{
    body.move(momentum);
}

void Entity::addVectorToMomentum(sf::Vector2f movement)
{
    momentum += movement;
    if (momentum.x > 3)
        momentum.x = 3;
    if (momentum.y > 3)
        momentum.y = 3;
}

void Entity::pushRightFromTexture(float deltaTime)
{
    sf::Vector2f movement(0,0);
    movement.x += deltaTime;
    move(movement);
}

void Entity::pushLeftFromTexture(float deltaTime)
{
    sf::Vector2f movement(0,0);
    movement.x -= deltaTime;
    move(movement);
}

void Entity::setTexture(sf::Texture* texture)
{
    body.setTexture(texture);
}

sf::Vector2f Entity::getMomentum() {
    return momentum;
}

void Entity::rotate(float angle)
{
    body.rotate(angle);
}

void Entity::setRotation(float angle)
{
    body.setRotation(angle);
}

void Entity::reverse()
{
    body.setScale(-1, 1);
}



