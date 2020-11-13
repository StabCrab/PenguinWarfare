//
// Created by trykr on 04.11.2020.
//

#include "Crosshair.h"

#include <cmath>
#include "iostream"
Crosshair::Crosshair(std::string texturePath, sf::Vector2f centerCoordinates)
{
    auto* texture = new sf::Texture;
    texture->loadFromFile(texturePath);
    crosshair.setTexture(texture);
    crosshair.setSize(sf::Vector2f(50,50));
    crosshair.setPosition(centerCoordinates);
}

Crosshair::~Crosshair()
{
    delete crosshair.getTexture();
}

void Crosshair::move(float deltaTime, bool isClockwise)
{
    deltaTime *= 70000 * speed;
    if (isClockwise)
    {
        if (crosshairVector.x >= 0 && crosshairVector.y < 0)
        {
            crosshairVector.x = std::sqrt(crosshairVector.x * crosshairVector.x + deltaTime);
            crosshairVector.y = -std::sqrt(crosshairVector.y * crosshairVector.y - deltaTime);
        }
        else if (crosshairVector.x > 0 && crosshairVector.y >= 0)
        {
            crosshairVector.x = std::sqrt(crosshairVector.x * crosshairVector.x - deltaTime);
            crosshairVector.y = std::sqrt(crosshairVector.y * crosshairVector.y + deltaTime);
        }
        else if (crosshairVector.x <= 0 && crosshairVector.y > 0)
        {
            crosshairVector.x = -std::sqrt(crosshairVector.x * crosshairVector.x + deltaTime);
            crosshairVector.y = std::sqrt(crosshairVector.y * crosshairVector.y - deltaTime);
        }
        else if (crosshairVector.x < 0 && crosshairVector.y <= 0)
        {
            crosshairVector.x = -std::sqrt(crosshairVector.x * crosshairVector.x - deltaTime);
            crosshairVector.y = -std::sqrt(crosshairVector.y * crosshairVector.y + deltaTime);
        }

    }
    else
    {
        if (crosshairVector.x > 0 && crosshairVector.y <= 0)
        {
            crosshairVector.x = std::sqrt(crosshairVector.x * crosshairVector.x - deltaTime);
            crosshairVector.y = -std::sqrt(crosshairVector.y * crosshairVector.y + deltaTime);
        }
        else if (crosshairVector.x >= 0 && crosshairVector.y > 0)
        {
            crosshairVector.x = std::sqrt(crosshairVector.x * crosshairVector.x + deltaTime);
            crosshairVector.y = std::sqrt(crosshairVector.y * crosshairVector.y - deltaTime);
        }
        else if (crosshairVector.x < 0 && crosshairVector.y >= 0)
        {
            crosshairVector.x = -std::sqrt(crosshairVector.x * crosshairVector.x - deltaTime);
            crosshairVector.y = std::sqrt(crosshairVector.y * crosshairVector.y + deltaTime);
        }
        else if (crosshairVector.x <= 0 && crosshairVector.y < 0)
        {
            crosshairVector.x = -std::sqrt(crosshairVector.x * crosshairVector.x + deltaTime);
            crosshairVector.y = -std::sqrt(crosshairVector.y * crosshairVector.y - deltaTime);
        }

    }
    if (_isnan(crosshairVector.y))
    {
        crosshairVector.y = 0;
        if (crosshairVector.x > 0)
            crosshairVector.x = RADIUS;
        else
            crosshairVector.x = -RADIUS;
    }
    if (_isnan(crosshairVector.x))
    {
        crosshairVector.x = 0;
        if (crosshairVector.y > 0)
            crosshairVector.y = RADIUS;
        else
            crosshairVector.y = -RADIUS;
    }
}

void Crosshair::draw(sf::RenderWindow& window, sf::Vector2f center)
{
    crosshair.setPosition(center + crosshairVector);
    window.draw(crosshair);
}

void Crosshair::clear(sf::Vector2f centerCoordinates)
{
    crosshairVector = sf::Vector2f(centerCoordinates + sf::Vector2f(sqrt(RADIUS),0));
}

sf::Vector2f Crosshair::getCrosshairVector() {
    return crosshairVector;
}

void Crosshair::reverseCrosshair()
{
    crosshairVector.x = -crosshairVector.x;
}

void Crosshair::increaseSpeed()
{
    if (speed < 16)
    speed *= 2.f;
}

void Crosshair::clearSpeed()
{
    speed = 1.f;
}