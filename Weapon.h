//
// Created by trykr on 19.10.2020.
//

#ifndef WORMSPROTOTYPE_WEAPON_H
#define WORMSPROTOTYPE_WEAPON_H
#include "Entity.h"
#include "Projectile.h"
#define WEAPONS_COUNT 1
enum class WeaponType
{
    RocketLauncher = 0,
    Grenade,
    AirStrike,

};
class Weapon
{
private:
    sf::Texture* weaponTexture;
    sf::Texture* projectileTexture;
    unsigned int damage;
    float explosionRadius;
    float massOfProjectile;
    sf::Vector2f projectileSize;
    sf::Vector2f weaponSize;
public:
    Weapon(std::string weaponTexturePath, std::string projectileTexturePath,
           int damage, float explosionRadius,float massOfProjectile,
           sf::Vector2f projectileSize, sf::Vector2f weaponSize);
    ~Weapon();
    float getExplosionRadius();
    unsigned int getDamage();
    sf::Texture* getProjectileTexture();
    sf::Texture* getWeaponTexture();
    float getMassOfProjectile();
    sf::Vector2f getProjectileSize();
    sf::Vector2f getWeaponSize();
};

class Bazooka: public Weapon
{
public:
    Bazooka();
};
#endif //WORMSPROTOTYPE_WEAPON_H
