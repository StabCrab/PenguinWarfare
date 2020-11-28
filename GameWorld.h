//
// Created by trykr on 16.10.2020.
//

#ifndef WORMSPROTOTYPE_GAMEWORLD_H
#define WORMSPROTOTYPE_GAMEWORLD_H
#include "Terrain.h"
#include "Player.h"
#include "algorithm"
#include "Projectile.h"
#include "Crosshair.h"
#include <thread>
enum class GameState
{
    unitWalking = 0,
    unitAiming,
    projectileFlying,
    consequences,
    lookingAround,
    shuttingDown
};
class GameWorld
{
private:
    Terrain terrain;
    sf::View view;
    const float gravity = 10;
    std::vector<Player*> playerVector;
    Unit* currentUnit;
    sf::RectangleShape* currentWeaponInHands;
    sf::RectangleShape powerMeter;
    sf::Texture* powerMeterTexture;
    unsigned int currentPlayerID = 0;
    GameState gameState = GameState::unitWalking;
    Weapon* weapons[WEAPONS_COUNT];
    Projectile* projectile;
    Crosshair* crosshair;
    bool isDownClockwise = true;
    float shootPower = 0;
    sf::Font font;
    float timer;
public:
    GameWorld(sf::RenderWindow& window, std::string level,
              const unsigned int numberOfPlayers,
              const int weaponCount[WEAPONS_COUNT]);
    ~GameWorld();
    GameState getGameState();
    void newTurn();
    void draw(sf::RenderWindow& window, float deltaTime);
    void keyPressedEvent(sf::Keyboard::Key, float deltaTime);
    void keyReleasedEvent(sf::Keyboard::Key, float deltaTime);
    void checkGravityAndCollision(float deltaTime);
    void shoot();
    void countShootPower(float deltaTime);
    void analisePlayers();
    void spawnUnit(Unit* unit);
};


#endif //WORMSPROTOTYPE_GAMEWORLD_H
