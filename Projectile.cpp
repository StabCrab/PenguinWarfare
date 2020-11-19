//
// Created by trykr on 01.11.2020.
//

#include "Projectile.h"

Projectile::Projectile(const std::string& texturePath, sf::Vector2f size, float mass, bool isBlowWhenCollides, int damage, float explosionRadius)
                       : Entity(texturePath, size, mass)
{
    this->isBlowWhenCollides = isBlowWhenCollides;
    this->damage = damage;
    this->explosionRadius = explosionRadius;
}

Projectile::~Projectile()
{

}

Projectile::Projectile(sf::Texture *texture, sf::Vector2f size, float mass, bool isBlowWhenCollides,
                       int damage, float explosionRadius)
                       : Entity(texture, size, mass)
{
    this->isBlowWhenCollides = isBlowWhenCollides;
    this->damage = damage;
    this->explosionRadius = explosionRadius;
}

unsigned int Projectile::getDamage()
{
    return damage;
}

float Projectile::getExplosionRadius()
{
    return explosionRadius;
}

bool Projectile::getIsBlowWhenCollides()
{
    return isBlowWhenCollides;
}

