//
// Created by trykr on 19.10.2020.
//

#include "Weapon.h"

Weapon::Weapon(std::string weaponTexturePath, std::string projectileTexturePath,
               int damage, float explosionRadius, float massOfProjectile,
               sf::Vector2f projectileSize, sf::Vector2f weaponSize)
{
    weaponTexture = new sf::Texture;
    projectileTexture = new sf::Texture;
    weaponTexture->loadFromFile(weaponTexturePath);
    projectileTexture->loadFromFile(projectileTexturePath);
    this->damage = damage;
    this->explosionRadius = explosionRadius;
    this->massOfProjectile = massOfProjectile;
    this->projectileSize = projectileSize;
    this->weaponSize = weaponSize;
}

Weapon::~Weapon()
{
    delete weaponTexture;
    delete projectileTexture;
}

float Weapon::getExplosionRadius() {
    return explosionRadius;
}

unsigned int Weapon::getDamage() {
    return damage;
}

float Weapon::getMassOfProjectile()
{
    return massOfProjectile;
}

sf::Vector2f Weapon::getProjectileSize()
{
    return projectileSize;
}
sf::Texture* Weapon:: getWeaponTexture()
{
    return weaponTexture;
}

sf::Texture* Weapon::getProjectileTexture()
{
    return projectileTexture;
}

sf::Vector2f Weapon::getWeaponSize() {
    return weaponSize;
}



//Bazooka::Bazooka()
//{
//    sf::Texture* texture = new sf::Texture;
//    texture->loadFromFile("RedPoint.png");
//
//}