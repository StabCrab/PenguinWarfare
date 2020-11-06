//
// Created by trykr on 01.11.2020.
//

#include "Projectile.h"

Projectile::Projectile(const std::string& texturePath, sf::Vector2f size, float mass, bool isBlowWhenCollides,
                       sf::Vector2f initialMomentum, int damage, float explosionRadius)
                       : Entity(texturePath, size, mass)
{
    this->isBlowWhenCollides = isBlowWhenCollides;
    addVectorToMomentum(initialMomentum);
    this->damage = damage;
    this->explosionRadius = explosionRadius;
}

Projectile::~Projectile()
{

}

Projectile::Projectile(sf::Texture *texture, sf::Vector2f size, float mass, bool isBlowWhenCollides,
                       sf::Vector2f initialMomentum, int damage, float explosionRadius)
                       : Entity(texture, size, mass)
{
    this->isBlowWhenCollides = isBlowWhenCollides;
    this->damage = damage;
    this->explosionRadius = explosionRadius;
}
