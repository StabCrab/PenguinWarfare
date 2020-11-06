//
// Created by trykr on 16.10.2020.
//

#ifndef WORMSPROTOTYPE_GAMEWORLD_H
#define WORMSPROTOTYPE_GAMEWORLD_H
#include "Terrain.h"
//#include "Unit.h" I dont want to include Unit now
#include "Player.h"
#include "algorithm"
#include "Projectile.h"
#include "Crosshair.h"
static const float VIEW_HEIGHT = 500.f;
class GameWorld
{
private:
    Terrain terrain;
    sf::View view;
    float deltaTime = 0.003;
    sf::Clock clock;
    const float gravity = 10;
    std::vector<std::unique_ptr<Player>> playerVector;
    Unit* currentUnit;
    sf::RectangleShape* currentWeaponInHands;
    unsigned int currentPlayerID = 0;
    bool isShooting = false;
    Weapon* weapons[WEAPONS_COUNT];
    Projectile* projectile;
    Crosshair* crosshair;
    bool isDownClockwise = true;
public:
    GameWorld(sf::RenderWindow& window, std::string level,
              const unsigned int numberOfPlayers,
              const int weaponCount[WEAPONS_COUNT]);
    ~GameWorld();
    void newTurn();
    void draw(sf::RenderWindow& window);
    void keyPressedEvent(sf::Keyboard::Key);
    void keyReleasedEvent(sf::Keyboard::Key);
    void checkGravityAndCollision();
    void shoot();
};


#endif //WORMSPROTOTYPE_GAMEWORLD_H
