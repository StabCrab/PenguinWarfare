//
// Created by trykr on 04.11.2020.
//

#ifndef PENGUINWARFARE_CROSSHAIR_H
#define PENGUINWARFARE_CROSSHAIR_H
#include "Graphics.hpp"
#include <cmath>

#define RADIUS 400
class Crosshair
{
private:
    sf::RectangleShape crosshair;
    sf::Vector2f crosshairVector = sf::Vector2f(RADIUS, 0);
    float speed = 1.f;
public:
    Crosshair(std::string texturePath, sf::Vector2f centerCoordinates);
    ~Crosshair();
    void move(float deltaTime, bool isClockwise);
    void draw(sf::RenderWindow& window, sf::Vector2f center);
    void clear(sf::Vector2f centerCoordinates);
    sf::Vector2f getCrosshairVector();
    void reverseCrosshair();
    void increaseSpeed();
    void clearSpeed();
};


#endif //PENGUINWARFARE_CROSSHAIR_H
