#include "Terrain.h"

Terrain::Terrain()
{
    sprite.setPosition(0,0);

}

Terrain::~Terrain()
{

}

void Terrain::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

sf::Color Terrain::getPixel(sf::Vector2f coordinates)
{
    return image.getPixel(coordinates.x, coordinates.y);
}

sf::Vector2f Terrain::getSpritePostition() {
    return sprite.getPosition();
}

void Terrain::setPixel(int x, int y)
{
    //image.setPixel(x, y, sf::Color::Red);
}

void Terrain::setTexture(std::string filename)
{


    image.loadFromFile(filename);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    terrainMaxY = sprite.getPosition().y + sprite.getTexture()->getSize().y;
    terrainMaxX = sprite.getPosition().x + sprite.getTexture()->getSize().x;
}

void Terrain::boom(sf::Vector2f position, float radius)
{

    for (float y = position.y - radius; y <= position.y + radius; ++y)
    {
        if (y < sprite.getPosition().y || y > terrainMaxY)
            continue;
        for (float x = position.x - radius; x <= position.x + radius; ++x)
        {
            if (x < sprite.getPosition().x || x > terrainMaxX)
                continue;
            double distance = std::sqrt(std::pow(x - position.x, 2) + std::pow(y - position.y, 2));

            if (distance <= radius) {
                image.setPixel(x - sprite.getPosition().x, y - sprite.getPosition().y, sf::Color::Transparent);
            }
        }
    }

    texture.loadFromImage(image);
    sprite.setTexture(texture);
}

int Terrain::getTerrainMaxX() {
    return terrainMaxX;
}

int Terrain::getTerrainMaxY()
{
    return terrainMaxY;
}
