//
// Created by trykr on 01.11.2020.
//

#ifndef PENGUINWARFARE_PROJECTILE_H
#define PENGUINWARFARE_PROJECTILE_H
#include "Entity.h"

class Projectile : public Entity
{
private:
    bool isBlowWhenCollides;
    unsigned int damage;
    float explosionRadius;
    bool isOutOfBounds = false;
public:
    Projectile(const std::string& texturePath, sf::Vector2f size, float mass, bool isBlowWhenCollides,
               int damage, float explosionRadius);
    Projectile(sf::Texture* texture, sf::Vector2f size, float mass, bool isBlowWhenCollides,
               int damage, float explosionRadius);
    ~Projectile();
    unsigned int getDamage();
    float getExplosionRadius();
    bool getIsBlowWhenCollides();

};


#endif //PENGUINWARFARE_PROJECTILE_H
