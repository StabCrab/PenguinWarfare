//
// Created by trykr on 11.10.2020.
//

#ifndef WORMSPROTOTYPE_TERRAIN_H
#define WORMSPROTOTYPE_TERRAIN_H
#include "SFML/Graphics.hpp"
#include "cmath"
class Terrain
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Image image;
    int terrainMaxY;
    int terrainMaxX;
public:
    Terrain();
    ~Terrain();
    void setTexture(std::string filename);
    void draw(sf::RenderWindow& window);
    sf::Color getPixel(sf::Vector2f coordinates);
    void setPixel(int x, int y);
    sf::Vector2f getSpritePostition();
    void boom(sf::Vector2f coordinates, float radius);
    int getTerrainMaxX();
    int getTerrainMaxY();
};
#endif //WORMSPROTOTYPE_TERRAIN_H
