//
// Created by trykr on 16.10.2020.
//

#include "GameWorld.h"

#include <cmath>
#include <memory>
#include <utility>
#include "iostream"
#include "cstdlib"
#include "ctime"

GameWorld::GameWorld(sf::RenderWindow& window, std::string level,
                     const unsigned int numberOfPlayers, const int weaponCount[WEAPONS_COUNT])
{
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Cannot find font"); //Throw exception if cannot find font
    }
    weapons[0] = new Weapon("Bazooka.png", "Rocket.png",
                            200, 100.f, 1.f,
                            sf::Vector2f(40,40), sf::Vector2f(100, 50));
    terrain.setTexture(std::move(level));
    powerMeterTexture = new sf::Texture;
    powerMeter.setSize(sf::Vector2f(200,100));
    powerMeterTexture->loadFromFile("PowerMeter.png");
    powerMeter.setTexture(powerMeterTexture);
    powerMeter.setOrigin(0, 40);
    view.setSize(1920, 1080);
    for (int i = 0; i < numberOfPlayers; i++)
    {
        if (i == 0)
        {
            playerVector.push_back(new Player(sf::Color::Red, weaponCount, &font));
            //playerVector[0]->getUnits()[0].setPosition(sf::Vector2f(5000, 2800));
            spawnUnit(playerVector[0]->getUnit(0));
            spawnUnit(playerVector[0]->getUnit(1));
            spawnUnit(playerVector[0]->getUnit(2));
            spawnUnit(playerVector[0]->getUnit(3));
        }
        if (i == 1)
        {
            playerVector.push_back(new Player(sf::Color::Blue, weaponCount, &font));
            //playerVector[1]->getUnits()[0].setPosition(sf::Vector2f(4000, 2800));
            spawnUnit(playerVector[1]->getUnit(0));
            spawnUnit(playerVector[1]->getUnit(1));
            spawnUnit(playerVector[1]->getUnit(2));
            spawnUnit(playerVector[1]->getUnit(3));
        }
        if (i == 2)
        {
            playerVector.push_back(new Player(sf::Color::Green, weaponCount, &font));
            spawnUnit(playerVector[2]->getUnit(0));
            spawnUnit(playerVector[2]->getUnit(1));
            spawnUnit(playerVector[2]->getUnit(2));
            spawnUnit(playerVector[2]->getUnit(3));
        }
        if (i == 3)
        {
            playerVector.push_back(new Player(sf::Color::Yellow, weaponCount, &font));
            spawnUnit(playerVector[3]->getUnit(0));
            spawnUnit(playerVector[3]->getUnit(1));
            spawnUnit(playerVector[3]->getUnit(2));
            spawnUnit(playerVector[3]->getUnit(3));
        }
    }
    currentUnit = playerVector[0]->getUnit(0);
    view.setCenter(currentUnit->getPosition());
    crosshair = new Crosshair("Crosshair.png", view.getCenter());
    currentWeaponInHands = new sf::RectangleShape;
    currentWeaponInHands->setSize(weapons[playerVector[0]->getCurrentWeaponID()]->getWeaponSize());
    currentWeaponInHands->setTexture(weapons[playerVector[0]->getCurrentWeaponID()]->getWeaponTexture());
    currentWeaponInHands->setOrigin(currentWeaponInHands->getSize().x / 2, currentWeaponInHands->getSize().y / 4);
}

GameWorld::~GameWorld()
{
    delete weapons[0];
    for (auto& player : playerVector)
        delete player;
    delete powerMeterTexture;
    delete crosshair;
}

void GameWorld::draw(sf::RenderWindow& window, float deltaTime)
{
    if (gameState == GameState::shuttingDown)
        return;
    if (deltaTime > 1)
        return;
    terrain.draw(window);
    checkGravityAndCollision(deltaTime);
    for (auto& player : playerVector)
    {
        for (int i = 0; i < UNIT_COUNTER; i++)
        {
            if (player->getUnit(i)->getIsOutOfBounds())
                continue;
            if (player->getUnit(i) != currentUnit)
            {
                player->getUnit(i)->draw(window, deltaTime);
                player->getUnit(i)->moveBody();
            }
        }
    }
    if (gameState == GameState::unitWalking)
    {
        view.setCenter(currentUnit->getPosition());
        crosshair->draw(window, view.getCenter());
    }
    else if (gameState == GameState::projectileFlying)
    {
        projectile->getBody().setRotation(90.f);
        projectile->moveBody();
        if (projectile->getMomentum().x < 0)
        {
            projectile->reverse();
        }
        projectile->setRotation(atanf(projectile->getMomentum().y / projectile->getMomentum().x) * 180 / 3.14);
        if (projectile->getPosition().y < 1040)
        {
            if (projectile->getIsOutOfBounds())
                view.setCenter(sf::Vector2f(projectile->getPseudoCoordinates().x, 1040));
            else
            {
                view.setCenter(sf::Vector2f(projectile->getPosition().x, 1040));
                projectile->drawBody(window);
            }
        }
        else
        {
            view.setCenter(projectile->getPosition());
            projectile->drawBody(window);
        }
    }
    else if (gameState == GameState::consequences)
    {
        bool isAnyoneMoving = false;
        for (auto& player : playerVector)
        {
            for (int i = 0; i < UNIT_COUNTER; i++)
            {
                if (player->getUnit(i)->getMomentum().x != 0
                && player->getUnit(i)->getMomentum().y != 0
                && player->getUnit(i)->getState() != UnitState::dead)
                    isAnyoneMoving = true;
            }
        }
        if (!isAnyoneMoving)
        {
            if (timer > 1)
            {
                analisePlayers();
                newTurn();
                if (gameState != GameState::shuttingDown)
                    gameState = GameState::unitWalking;
            }
            else
                timer += deltaTime;
        }
    }
    else if (gameState== GameState::unitAiming)
    {
        if (currentUnit->getIsFaceRight())
            powerMeter.setScale(shootPower * 15.f, shootPower * 15.f);
        else
            powerMeter.setScale(-shootPower * 15.f, shootPower * 15.f);
        powerMeter.setRotation(atanf(crosshair->getCrosshairVector().y / crosshair->getCrosshairVector().x) * 180 / 3.14);
        powerMeter.setPosition(currentUnit->getPosition());
        window.draw(powerMeter);
    }
    window.setView(view);

    currentUnit->draw(window, deltaTime);
    currentUnit->moveBody();

    currentWeaponInHands->setPosition(currentUnit->getPosition());
    currentWeaponInHands->setRotation(atanf(crosshair->getCrosshairVector().y / crosshair->getCrosshairVector().x) * 180 / 3.14);
    window.draw(*currentWeaponInHands);
}

void GameWorld::keyPressedEvent(sf::Keyboard::Key key, float deltaTime)
{
    if (terrain.getPixel(currentUnit->getBottomCoordinates()) == sf::Color::Transparent
        && terrain.getPixel(currentUnit->getLeftBottomCoordinates()) == sf::Color::Transparent &&
        terrain.getPixel(currentUnit->getRightBottomCoordinates()) == sf::Color::Transparent)
    {
        return;
    }
    if (gameState == GameState::consequences)
    {
        return;
    }
    if (key == sf::Keyboard::D)
    {
        if (gameState == GameState::lookingAround)
        {
            if (view.getCenter().x < 7000)
                view.setCenter(sf::Vector2f(view.getCenter().x + deltaTime * 5000.f, view.getCenter().y));
        }
        if (gameState != GameState::unitWalking)
            return;

        currentUnit->walk(deltaTime, true);
        if (crosshair->getCrosshairVector().x < 0)
        {
            crosshair->reverseCrosshair();
            isDownClockwise = true;
        }
        currentWeaponInHands->setScale(1, 1);

    }
    if (key == sf::Keyboard::A)
    {
        if (gameState == GameState::lookingAround)
        {
            if (view.getCenter().x > 1000)
                view.setCenter(sf::Vector2f(view.getCenter().x - deltaTime * 5000.f, view.getCenter().y));
        }
        if (gameState != GameState::unitWalking)
            return;
        currentUnit->walk(deltaTime, false);
        if (crosshair->getCrosshairVector().x > 0)
        {
            crosshair->reverseCrosshair();
            isDownClockwise = false;
        }
        currentWeaponInHands->setScale(-1, 1);
    }
    if (key == sf::Keyboard::Enter)
    {
        if (gameState == GameState::unitWalking)
        {
            if (currentUnit->getState() == UnitState::walking)
                currentUnit->idle(deltaTime);
            gameState = GameState::lookingAround;
            view.setSize(2560, 1720);
        }
        else if (gameState == GameState::lookingAround)
        {
            view.setSize(1920, 1080);
            gameState = GameState::unitWalking;
        }
    }
    if (key == sf::Keyboard::Space)
    {
        if (currentUnit->getState() != UnitState::idle)
            return;
        if (gameState == GameState::unitWalking)
            gameState = GameState::unitAiming;
        if (gameState == GameState::unitAiming)
            countShootPower(deltaTime);
    }
    if (key == sf::Keyboard::Num1)
    {
        playerVector[currentPlayerID]->setCurrentWeaponID(0);
    }
    if (key == sf::Keyboard::W)
    {
        if (gameState == GameState::lookingAround)
        {
            return;
        }
        crosshair->move(deltaTime, !isDownClockwise);
        if (crosshair->getCrosshairVector().x < 0)
            currentUnit->setIsFaceRight(false);
        if (crosshair->getCrosshairVector().x > 0)
            currentUnit->setIsFaceRight(true);
        crosshair->increaseSpeed();

        if (crosshair->getCrosshairVector().x < 0)
            currentWeaponInHands->setScale(-1, 1);
        else
            currentWeaponInHands->setScale(1, 1);
    }
    if (key == sf::Keyboard::S)
    {
        if (gameState == GameState::lookingAround)
        {
            return;
        }
        crosshair->move(deltaTime, isDownClockwise);
        if (crosshair->getCrosshairVector().x < 0)
            currentUnit->setIsFaceRight(false);
        if (crosshair->getCrosshairVector().x > 0)
            currentUnit->setIsFaceRight(true);
        crosshair->increaseSpeed();

        if (crosshair->getCrosshairVector().x < 0)
            currentWeaponInHands->setScale(-1, 1);
        else
            currentWeaponInHands->setScale(1, 1);
    }

}

void GameWorld::keyReleasedEvent(sf::Keyboard::Key key, float deltaTime)
{
    if (key == sf::Keyboard::Escape)
    {
        gameState = GameState::shuttingDown;
    }
    if (gameState == GameState::consequences)
    {
        return;
    }
    if (gameState == GameState::lookingAround)
        return;
    if (key == sf::Keyboard::D || key == sf::Keyboard::A)
        currentUnit->idle(deltaTime);
    if (key == sf::Keyboard::W || key == sf::Keyboard::S)
    {
        if (crosshair->getCrosshairVector().x > 0)
            isDownClockwise = true;
        if (crosshair->getCrosshairVector().x < 0)
            isDownClockwise = false;
        crosshair->clearSpeed();
    }
    if (key == sf::Keyboard::Space)
    {
        if (currentUnit->getState() != UnitState::idle)
            return;
        shoot();
    }
    if (key == sf::Keyboard::Q)
    {
        if (abs(currentUnit->getMomentum().x) > 1 || abs(currentUnit->getMomentum().y) > 1)
        {
            return;
        }
        if (currentUnit->getIsFaceRight())
            currentUnit->jumpBackwards();
        else
            currentUnit->jumpForward();
    }
    if (key == sf::Keyboard::E)
    {
        if (abs(currentUnit->getMomentum().x) > 1 || abs(currentUnit->getMomentum().y) > 1)
        {
            return;
        }
        if (currentUnit->getIsFaceRight())
            currentUnit->jumpForward();
        else
            currentUnit->jumpBackwards();
    }
}

void GameWorld::newTurn()
{
    currentPlayerID++;
    if (currentPlayerID >= playerVector.size())
        currentPlayerID = 0;
    while(playerVector[currentPlayerID]->getIsDefeated())
    {
        currentPlayerID++;
        if (currentPlayerID >= playerVector.size())
            currentPlayerID = 0;
    }
    playerVector[currentPlayerID]->setNextCurrentUnit();
    if (playerVector[currentPlayerID]->getIsDefeated() == true)
        newTurn();
    currentUnit = playerVector[currentPlayerID]->getCurrentUnit();
    crosshair->clear(currentUnit->getIsFaceRight());
    if (currentUnit->getIsFaceRight())
        currentWeaponInHands->setScale(1,1);
    else
        currentWeaponInHands->setScale(-1,1);
}

void GameWorld::checkGravityAndCollision(float deltaTime)
{
    if (gameState == GameState::projectileFlying)
    {
        if (terrain.getPixel(projectile->getPosition()) != sf::Color::Transparent)
        {
            sf::Vector2f distanceVector;
            float distance;
            for (auto& player : playerVector)
            {
                for (int i = 0; i < UNIT_COUNTER; i++)
                {
                    if (player->getUnit(i)->getIsOutOfBounds())
                        continue;
                    distanceVector =  player->getUnit(i)->getPosition() - projectile->getPosition();
                    distance = sqrt(distanceVector.x * distanceVector.x
                            + distanceVector.y * distanceVector.y);
                    if (distance < projectile->getExplosionRadius() + 50)
                    {
                        player->getUnit(i)->takeDamage(distanceVector * 30.f / distance
                                                         , projectile->getDamage() / (distance / 10.f));
                    }
                }
            }
            terrain.boom(projectile->getPosition(),
                         projectile->getExplosionRadius());
            delete projectile;
            timer = 0;
            gameState = GameState::consequences;
        }
        else
        {
            projectile->fall(deltaTime, gravity);
        }
        if (projectile->getPosition().x > terrain.getTerrainMaxX() ||
            projectile->getPosition().x < terrain.getSpritePostition().x)
        {
            delete projectile;
            gameState = GameState::consequences;
        }

    }
    for (auto& player : playerVector)
    {
        for (int i = 0; i < UNIT_COUNTER; i++)
        {
            if (player->getUnit(i)->getIsOutOfBounds())
                continue;
            if (terrain.getPixel(player->getUnit(i)->getBottomCoordinates()) == sf::Color::Transparent
                && terrain.getPixel(player->getUnit(i)->getLeftBottomCoordinates()) == sf::Color::Transparent &&
                terrain.getPixel(player->getUnit(i)->getRightBottomCoordinates()) == sf::Color::Transparent)
            {
                player->getUnit(i)->fall(deltaTime,gravity);
            }
            else if (player->getUnit(i)->getMomentum().y >= 0
            && player->getUnit(i)->getState() != UnitState::walking && player->getUnit(i)->getMomentum().x != 0)
                player->getUnit(i)->frictionForce();
            while ((terrain.getPixel(player->getUnit(i)->getBottomCoordinates()) != sf::Color::Transparent))
            {
                player->getUnit(i)->pushUpFromTexture(deltaTime);
            }
            while (((terrain.getPixel(player->getUnit(i)->getLeftCoordinates()) != sf::Color::Transparent)))
            {
                player->getUnit(i)->pushRightFromTexture(deltaTime);
            }
            while (((terrain.getPixel(player->getUnit(i)->getRightCoordinates()) != sf::Color::Transparent)))
            {
                player->getUnit(i)->pushLeftFromTexture(deltaTime);
            }
            if (player->getUnit(i)->getBottomCoordinates().y > 2900 ||
            player->getUnit(i)->getPosition().x < 0 || player->getUnit(i)->getPosition().x > 8000)
            {
                player->getUnit(i)->makeUnitOutOfBounds();
                if (player->getUnit(i) == currentUnit)
                    gameState = GameState::consequences;
            }
        }
    }
}


void GameWorld::shoot()
{
    if (gameState == GameState::projectileFlying)
        return;
    projectile = new Projectile(weapons[0]->getProjectileTexture(), weapons[0]->getProjectileSize(),
                                weapons[0]->getMassOfProjectile(),  true,
                                weapons[0]->getDamage(), weapons[0]->getExplosionRadius());
    projectile->setPosition(currentUnit->getPosition());
    projectile->addVectorToMomentum(crosshair->getCrosshairVector() * shootPower);
    shootPower = 0;
    gameState = GameState::projectileFlying;
}

void GameWorld::countShootPower(float deltaTime)
{
    if (shootPower < 0.1)
    {
        shootPower += deltaTime / 20.f;
    }
}

void GameWorld::analisePlayers()
{
    short int notDefeatedCount = 0;
    for (auto& player : playerVector)
    {
        player->analiseSituation();
        if (player->getIsDefeated() == false)
            notDefeatedCount++;
    }
    if (notDefeatedCount == 1)
        gameState = GameState::shuttingDown;
}

void GameWorld::spawnUnit(Unit* unit)
{
    sf::Vector2f coordinates(rand() % 6000 + 1000, 2800);
    while (terrain.getPixel(coordinates) == sf::Color::Transparent)
    {
        coordinates = sf::Vector2f(rand() % 6000 + 1000, 2800);
    }
    unit->setPosition(coordinates);
}

GameState GameWorld::getGameState()
{
    return gameState;
}
