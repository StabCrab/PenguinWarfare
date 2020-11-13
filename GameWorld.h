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
#include <thread>
enum class GameState
{
    unitWalking = 0,
    unitAiming,
    projectileFlying,
    consequences

};
class GameWorld
{
private:
    Terrain terrain;
    sf::View view;
    float deltaTime = 0.003;
    sf::Clock clock;
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
    void newTurn();
    void draw(sf::RenderWindow& window);
    void keyPressedEvent(sf::Keyboard::Key);
    void keyReleasedEvent(sf::Keyboard::Key);
    void checkGravityAndCollision();
    void shoot();
    void countShootPower();
    void analisePlayers();
    void spawnUnit(Unit* unit);
};


#endif //WORMSPROTOTYPE_GAMEWORLD_H
