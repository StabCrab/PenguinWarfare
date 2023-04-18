//
// Created by trykr on 16.10.2020.
//

#include "GameWorld.h"

#include <cmath>
#include <memory>
#include <utility>
#include <sstream>
#include "iostream"
#include "cstdlib"
#include "ctime"

GameWorld::GameWorld(sf::RenderWindow& window, std::string level,
                     const unsigned int numberOfPlayers)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Cannot find font"); //Throw exception if cannot find font
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Yellow);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    terrain.setTexture(std::move(level));
    view.setSize(1920, 1080);
    for (int i = 0; i < numberOfPlayers; i++)
    {
        if (i == 0)
        {
            playerVector.push_back(new Player(sf::Color::Red, &font));
            spawnUnit(playerVector[0]->getUnit(0));
        }
    }
    currentUnit = playerVector[0]->getUnit(0);
    view.setCenter(currentUnit->getPosition());
    chest = new Entity("chest.png", sf::Vector2f(80, 80), 5);
    chest->setPosition(sf::Vector2f(3147, 1511));
    door = new Entity("door.png", sf::Vector2f(240,240), 5);
    door->setPosition(sf::Vector2f(4595, 2100));
}

GameWorld::~GameWorld()
{
    for (auto& player : playerVector)
        delete player;
}

void GameWorld::draw(sf::RenderWindow& window, float deltaTime)
{
    this->deltaTime = deltaTime;
    text.setString(s);
    if (isCommandsLeft && currentUnit->getState() == UnitState ::idle &&(terrain.getPixel(currentUnit->getBottomCoordinates()) != sf::Color::Transparent
                                                                        || terrain.getPixel(currentUnit->getLeftBottomCoordinates()) != sf::Color::Transparent ||
                                                                        terrain.getPixel(currentUnit->getRightBottomCoordinates()) != sf::Color::Transparent))
    {
        Efunc();
    }


    door->drawBody(window);
    chest->drawBody(window);
    clock_t a = clock();
    if (until > a)
    {
        movement(isGoingLeft);
    }
    else if (currentUnit->getGoingToChest())
    {
        if (chest->getPosition().x < currentUnit->getPosition().x)
        {
            movement(true);
        }
        else if (chest->getPosition().x > currentUnit->getPosition().x)
        {
            movement(false);
        }

        if (std::abs(currentUnit->getPosition().x - chest->getPosition().x) < 50 || std::abs(chest->getPosition().y - currentUnit->getPosition().y) > 200)
        {
            currentUnit->stopGoingToChest();
        }
    }
    else if (currentUnit->getGoingToDoor())
    {
        if (door->getPosition().x < currentUnit->getPosition().x)
        {
            movement(true);
        }
        else if (door->getPosition().x > currentUnit->getPosition().x)
        {
            movement(false);
        }

        if (std::abs(currentUnit->getPosition().x - door->getPosition().x) < 50  || std::abs(door->getPosition().y - currentUnit->getPosition().y) > 200)
        {
            currentUnit->stopGoingToDoor();
        }
    }

    else
    {
        if (currentUnit->getState() != UnitState::idle)
        {
            currentUnit->idle(deltaTime);
        }
    }
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
    }
    window.setView(view);


    text.setPosition(view.getCenter().x - s.size() * 8, view.getCenter().y - 500);
    window.draw(text);
    currentUnit->draw(window, deltaTime);
    currentUnit->moveBody();
}

void GameWorld::keyPressedEvent(sf::Keyboard::Key key, float deltaTime)
{
    if (gameState == GameState::consequences)
    {
        return;
    }
    if (s == "Victory" || s =="Key acquired")
        s.clear();
    switch (key)
    {
        case sf::Keyboard::Q:
            s+='Q';
            break;
        case sf::Keyboard::W:
            s+='W';
            break;
        case sf::Keyboard::E:
            s+='E';
            break;
        case sf::Keyboard::R:
            s+='R';
            break;
        case sf::Keyboard::T:
            s+= 'T';
            break;
        case sf::Keyboard::Y:
            s+= 'Y';
            break;
        case sf::Keyboard::U:
            s+= 'U';
            break;
        case sf::Keyboard::I:
            s+= 'I';
            break;
        case sf::Keyboard::O:
            s+= 'O';
            break;
        case sf::Keyboard::P:
            s+='P';
            break;
        case sf::Keyboard::A:
            s+='A';
            break;
        case sf::Keyboard::S:
            s+='S';
            break;
        case sf::Keyboard::D:
            s+='D';
            break;
        case sf::Keyboard::F:
            s+= 'F';
            break;
        case sf::Keyboard::G:
            s+= 'G';
            break;
        case sf::Keyboard::H:
            s+= 'H';
            break;
        case sf::Keyboard::J:
            s+= 'J';
            break;
        case sf::Keyboard::K:
            s+= 'K';
            break;
        case sf::Keyboard::L:
            s+= 'L';
            break;
        case sf::Keyboard::Z:
            s+= 'Z';
            break;
        case sf::Keyboard::X:
            s+= 'X';
            break;
        case sf::Keyboard::C:
            s+= 'C';
            break;
        case sf::Keyboard::V:
            s+='V';
            break;
        case sf::Keyboard::B:
            s+='B';
            break;
        case sf::Keyboard::N:
            s+='N';
            break;
        case sf::Keyboard::M:
            s+='M';
            break;
        case sf::Keyboard::Num0:
            s+= '0';
            break;
        case sf::Keyboard::Num1:
            s+= '1';
            break;
        case sf::Keyboard::Num2:
            s+= '2';
            break;
        case sf::Keyboard::Num3:
            s+= '3';
            break;
        case sf::Keyboard::Num4:
            s+='4';
            break;
        case sf::Keyboard::Num5:
            s+='5';
            break;
        case sf::Keyboard::Num6:
            s+='6';
            break;
        case sf::Keyboard::Num7:
            s+='7';
            break;
        case sf::Keyboard::Num8:
            s+='8';
            break;
        case sf::Keyboard::Num9:
            s+='9';
            break;
        case sf::Keyboard::Space:
            s+=' ';
            break;
        case sf::Keyboard::Enter:
        {
            if (until == INT_MAX)
            {
                Stop();
            }
            remain = s;
            s.clear();
            isCommandsLeft = true;
            break;
        }
        case sf::Keyboard::BackSpace:
            if (!s.empty())
                s.pop_back();
            break;
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
    currentUnit = playerVector[currentPlayerID]->getCurrentUnit();
}

void GameWorld::checkGravityAndCollision(float deltaTime)
{
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




void GameWorld::spawnUnit(Unit* unit)
{
    sf::Vector2f coordinates(1000, 2000);
    unit->setPosition(coordinates);
}

GameState GameWorld::getGameState()
{
    return gameState;
}

void GameWorld::parse()
{
    Efunc();
    s.clear();
}

void GameWorld::movement(bool isLeft)
{
    if (isLeft)
    {
        currentUnit->walk(deltaTime, false);
    }
    else
    {
        currentUnit->walk(deltaTime, true);
    }
}

bool GameWorld::isNumber(std::string string) {
    for (char const &ch : string)
    {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}

void GameWorld::Efunc()
{
    currentUnit->stopGoingToChest();
    currentUnit->stopGoingToDoor();
    scan();
    if (curWord == "STOP")
    {
        Stop();
    }
    if (curWord == "GO")
    {
        scan();
        if (curWord == "RIGHT" || curWord == "LEFT")
        {
            Dir();
        }
        else if (curWord == "TO")
        {
            Item();
        }
    }
    if (curWord == "JUMP" || curWord == "TURN")
    {
        scan();
        Dir();
    }
    if (curWord == "OPEN")
    {
        Item();
    }
    if (curWord == "DOIT")
    {
        remain = "GO RIGHT 2 TURN LEFT JUMP RIGHT GO LEFT 2 TURN RIGHT JUMP LEFT GO RIGHT 2 TURN LEFT JUMP RIGHT TURN RIGHT JUMP RIGHT GO TO CHEST OPEN CHEST GO RIGHT 3  GO TO DOOR OPEN DOOR";
    }
    if (remain.empty())
        isCommandsLeft = false;
}

void GameWorld::Stop()
{
    until = -2;
}

void GameWorld::scan()
{
    prevWord = curWord;
    if (remain.empty())
    {
        curWord = "";
    }
    int i = remain.find(' ');
    std::string a;
    if (i == -1)
    {
        curWord = remain;
        remain.clear();
    }
    else
    {
        curWord =  remain.substr(0,i);
        remain = remain.substr(i + 1);
    }
}



void GameWorld::Dir()
{
    if (curWord == "RIGHT")
    {
        if (prevWord == "GO")
        {
            scan();
            if (curWord.empty())
            {
                until = INT_MAX;
            }
            else
            {
                num();
            }
            isGoingLeft = false;
        }
        else if (prevWord == "JUMP")
        {
            if (currentUnit->getIsFaceRight())
            {
                currentUnit->jumpForward(deltaTime);
            }
            else
            {
                currentUnit->jumpBackwards(deltaTime);
            }
        }
        else if (prevWord == "TURN")
        {
            currentUnit->walk(deltaTime, true);
        }
    }
    else if (curWord == "LEFT")
    {
        if (prevWord == "GO")
        {
            scan();
            if (curWord.empty())
            {
                until = INT_MAX;
            }
            else
            {
                num();
            }
            isGoingLeft = true;
        }
        else if (prevWord == "JUMP")
        {
            if (currentUnit->getIsFaceRight())
            {
                currentUnit->jumpBackwards(deltaTime);
            }
            else
            {
                currentUnit->jumpForward(deltaTime);
            }
        }
        else if (prevWord == "TURN")
        {
            currentUnit->walk(deltaTime, false);
        }
    }
}

void GameWorld::Item()
{
    scan();
    if (curWord == "CHEST")
    {
        if (prevWord == "OPEN")
        {
            if (std::abs(currentUnit->open().x - chest->getPosition().x) < 100 && std::abs(currentUnit->open().y - chest->getPosition().y) < 100)
            {
                currentUnit->giveKey();
                s = "Key acquired";
            }
        }
        else if (prevWord == "TO")
        {
            if (std::abs(chest->getPosition().y - currentUnit->getPosition().y) < 100)
            {
                currentUnit->goToChest();
            }
        }
    }
    if (curWord == "DOOR")
    {
        if (prevWord == "OPEN")
        {
            if (std::abs(currentUnit->open().x - door->getPosition().x) < 100 && std::abs(currentUnit->open().y - door->getPosition().y) < 100 && currentUnit->getHasKey())
                s = "Victory";
        }
        else if (prevWord == "TO")
        {
            if (std::abs(door->getPosition().y - currentUnit->getPosition().y) < 100)
            {
                currentUnit->goToDoor();
            }
        }
    }
}

void GameWorld::num()
{
    if (isNumber(curWord))
    {
        until = clock() + std::stoi(curWord) * 500;
    }
    else
    {
        until = INT_MAX;
    }
}
