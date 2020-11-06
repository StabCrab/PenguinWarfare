//
// Created by trykr on 16.10.2020.
//

#include "GameWorld.h"

#include <cmath>
#include <memory>
#include <utility>
#include "iostream"

GameWorld::GameWorld(sf::RenderWindow& window, std::string level,
                     const unsigned int numberOfPlayers,
                     const int weaponCount[WEAPONS_COUNT])
{
    weapons[0] = new Weapon("Bazooka.png", "Rocket.png",
                            30, 50.f, 5.f,
                            sf::Vector2f(40,40), sf::Vector2f(100, 50));
    terrain.setTexture(std::move(level));
    view.setSize(1920, 1080);
    for (int i = 0; i < numberOfPlayers; i++)
    {
        if (i == 0)
        {
            playerVector.push_back(std::make_unique<Player>(sf::Color::Red, weaponCount));
            playerVector[0]->getUnits()[0].setPosition(sf::Vector2f(0,500));
        }
        if (i == 1)
        {
            playerVector.push_back(std::make_unique<Player>(sf::Color::Blue, weaponCount));
            playerVector[1]->getUnits()[0].setPosition(sf::Vector2f(10,10));
        }
        if (i == 2)
        {
            playerVector.push_back(std::make_unique<Player>(sf::Color::Green, weaponCount));
        }
        if (i == 3)
        {
            playerVector.push_back(std::make_unique<Player>(sf::Color::Yellow, weaponCount));
        }
    }
    currentUnit = &playerVector[0]->getUnits()[0];
    view.setCenter(currentUnit->getPosition());
    crosshair = new Crosshair("Crosshair.png", view.getCenter());
    currentWeaponInHands = new sf::RectangleShape;
    currentWeaponInHands->setSize(weapons[playerVector[0]->getCurrentWeaponID()]->getWeaponSize());
    currentWeaponInHands->setTexture(weapons[playerVector[0]->getCurrentWeaponID()]->getWeaponTexture());
    currentWeaponInHands->setOrigin(currentWeaponInHands->getSize().x / 2, currentWeaponInHands->getSize().y / 4);
}

GameWorld::~GameWorld() {

}

void GameWorld::draw(sf::RenderWindow& window)
{
    terrain.draw(window);
    if (!isShooting)
        view.setCenter(currentUnit->getPosition());
    else
    {
        view.setCenter(projectile->getPosition());
        projectile->getBody().setRotation(90.f);
        projectile->moveBody();
        if (projectile->getMomentum().x < 0)
        {
            projectile->reverse();
        }
        projectile->setRotation(atanf(projectile->getMomentum().y / projectile->getMomentum().x) * 180 / 3.14);
        projectile->drawBody(window);
    }
    window.setView(view);
    checkGravityAndCollision();
    for (auto& player : playerVector)
    {
        for (int i = 0; i < UNIT_COUNTER; i++)
        {
            player->getUnits()[i].draw(window, deltaTime);
            player->getUnits()[i].moveBody();
        }
    }
    crosshair->draw(window, view.getCenter());
    currentWeaponInHands->setPosition(currentUnit->getPosition());
    currentWeaponInHands->setRotation(atanf(crosshair->getCrosshairVector().y / crosshair->getCrosshairVector().x) * 180 / 3.14);
    window.draw(*currentWeaponInHands);
}

void GameWorld::keyPressedEvent(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::D)
    {
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
        newTurn();
    }
    if (key == sf::Keyboard::Space)
    {
        shoot();
    }
    if (key == sf::Keyboard::Num1)
    {
        playerVector[currentPlayerID]->setCurrentWeaponID(0);
    }
    if (key == sf::Keyboard::W)
    {
        crosshair->move(deltaTime, !isDownClockwise);
        if (crosshair->getCrosshairVector().x < 0)
            currentUnit->setIsFaceRight(false);
        if (crosshair->getCrosshairVector().x > 0)
            currentUnit->setIsFaceRight(true);
    }
    if (key == sf::Keyboard::S)
    {
        crosshair->move(deltaTime, isDownClockwise);
        if (crosshair->getCrosshairVector().x < 0)
            currentUnit->setIsFaceRight(false);
        if (crosshair->getCrosshairVector().x > 0)
            currentUnit->setIsFaceRight(true);
    }

}

void GameWorld::newTurn()
{
    currentUnit->idle(deltaTime);
    playerVector[currentPlayerID]->setNextCurrentUnit();
    currentPlayerID++;
    if (currentPlayerID >= playerVector.size())
        currentPlayerID = 0;
    currentUnit = playerVector[currentPlayerID]->getCurrentUnit();
}

void GameWorld::checkGravityAndCollision()
{
    if (isShooting)
    {
        if (terrain.getPixel(projectile->getPosition()) != sf::Color::Transparent)
        {
            terrain.boom(projectile->getPosition(), 30);
            delete projectile;
            isShooting = false;
        }
        if (projectile->getPosition().x > terrain.getTerrainMaxX() ||
            projectile->getPosition().x < terrain.getSpritePostition().x ||
            projectile->getPosition().y > terrain.getTerrainMaxY() ||
            projectile->getPosition().y < terrain.getSpritePostition().y)
        {
            delete projectile;
            isShooting = false;
        }

    }
    for (auto& player : playerVector)
    {
        for (int i = 0; i < UNIT_COUNTER; i++)
        {
            if (terrain.getPixel(player->getUnits()->getBottomCoordinates()) == sf::Color::Transparent
                && terrain.getPixel(player->getUnits()->getLeftBottomCoordinates()) == sf::Color::Transparent &&
                terrain.getPixel(player->getUnits()->getRightBottomCoordinates()) == sf::Color::Transparent)
            {
                player->getUnits()[i].fall(deltaTime,gravity);
            }
            while ((terrain.getPixel(player->getUnits()->getBottomCoordinates()) != sf::Color::Transparent))
            {
                player->getUnits()[i].pushUpFromTexture(deltaTime);
            }
            while (((terrain.getPixel(player->getUnits()->getLeftCoordinates()) != sf::Color::Transparent)))
            {
                player->getUnits()[i].pushRightFromTexture(deltaTime);
            }
            while (((terrain.getPixel(player->getUnits()->getRightCoordinates()) != sf::Color::Transparent)))
            {
                player->getUnits()[i].pushLeftFromTexture(deltaTime);
            }
        }

    }
}

void GameWorld::keyReleasedEvent(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::D || key == sf::Keyboard::A)
        currentUnit->idle(deltaTime);
    if (key == sf::Keyboard::W || key == sf::Keyboard::S)
    {
        if (crosshair->getCrosshairVector().x > 0)
            isDownClockwise = true;
        if (crosshair->getCrosshairVector().x < 0)
            isDownClockwise = false;
    }
}

void GameWorld::shoot()
{
    if (isShooting)
        return;
    projectile = new Projectile(weapons[0]->getProjectileTexture(), weapons[0]->getProjectileSize(),
                                weapons[0]->getMassOfProjectile(),  true, sf::Vector2f(50,0),
                                weapons[0]->getDamage(), weapons[0]->getExplosionRadius());
    projectile->setPosition(currentUnit->getPosition());
    projectile->addVectorToMomentum(crosshair->getCrosshairVectorForShooting());
    isShooting = true;
}
