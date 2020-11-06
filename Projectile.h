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
    int damage;
    float explosionRadius;
public:
    Projectile(const std::string& texturePath, sf::Vector2f size, float mass, bool isBlowWhenCollides,
               sf::Vector2f initialMomentum, int damage, float explosionRadius);
    Projectile(sf::Texture* texture, sf::Vector2f size, float mass, bool isBlowWhenCollides,
               sf::Vector2f initialMomentum, int damage, float explosionRadius);
    ~Projectile();

};


#endif //PENGUINWARFARE_PROJECTILE_H
