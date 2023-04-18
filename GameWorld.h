//
// Created by trykr on 16.10.2020.
//

#ifndef WORMSPROTOTYPE_GAMEWORLD_H
#define WORMSPROTOTYPE_GAMEWORLD_H
#include "Terrain.h"
#include "Player.h"
#include "algorithm"
#include <thread>
#include<ctime>

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
    const float gravity = 10.f;
    std::vector<Player*> playerVector;
    Unit* currentUnit;
    unsigned int currentPlayerID = 0;
    GameState gameState = GameState::unitWalking;
    float shootPower = 0;
    sf::Font font;
    sf::Text text;
    std::string s = "";
    clock_t now;
    clock_t until = 0;
    bool isGoingLeft;
    Entity* chest;
    Entity* door;
    std::string curWord = "";
    std::string prevWord = "";
    bool isCommandsLeft = false;
    float deltaTime;

    void Efunc();
    void Dir();
    void Item();

    void num();
    void Stop();
    void scan();

    std::string remain;
public:
    GameWorld(sf::RenderWindow& window, std::string level,
              const unsigned int numberOfPlayers);
    ~GameWorld();
    GameState getGameState();
    void newTurn();
    void draw(sf::RenderWindow& window, float deltaTime);
    void keyPressedEvent(sf::Keyboard::Key, float deltaTime);
    void keyReleasedEvent(sf::Keyboard::Key, float deltaTime);
    void checkGravityAndCollision(float deltaTime);
    void spawnUnit(Unit* unit);
    void parse();
    void movement(bool isLeft);
    bool isNumber(const std::string s);
};


#endif //WORMSPROTOTYPE_GAMEWORLD_H
