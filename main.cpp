#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameWorld.h"
#include "ctime"
enum class CurrentClass{menu = 0, game, pause};

int main(int argc, char* argv[])
{
    sf::Clock clock;
    sf::Time deltaTime;
    int width = 1920;
    int height = 1080;

    sf::RenderWindow window(sf::VideoMode(width, height),
                            "Penguin Warfare");
    window.setVerticalSyncEnabled(true);
    window.setTitle("Penguin Warfare");

    Menu* menu = new Menu(window.getSize());
    GameWorld* gameWorld;

    CurrentClass currentClass = CurrentClass::menu;
    clock.restart();
    while (window.isOpen()) // While window is open
    {
        deltaTime = clock.getElapsedTime();
        clock.restart();

        sf::Event event{};
        while (window.pollEvent(event)) // We check for events
        {
            if (event.type == sf::Event::Closed) // Request for closing the window
                window.close();
            if (currentClass == CurrentClass::menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    menu->keyPressedEvent(event.key.code);
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    menu->keyReleasedEvent(event.key.code);
                }
            }
            else if (currentClass == CurrentClass::game)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    gameWorld->keyPressedEvent(event.key.code, deltaTime.asSeconds());
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    gameWorld->keyReleasedEvent(event.key.code,deltaTime.asSeconds());
                }
            }

        }
        window.clear(sf::Color(150,150,150)); // Clear the whole window before rendering a new frame
        if (currentClass == CurrentClass::menu)
        {
            if (menu->getMenuState() == MenuState::generalMenu
            || menu->getMenuState() == MenuState::gameStartOptions)
            {
                menu->draw(window);
            }
            else if (menu->getMenuState() == MenuState::startingGame)
            {
                clock.restart();
                currentClass = CurrentClass::game;
                int array[1];
                array[0] = 999;
                gameWorld = new GameWorld(window, "terrainB.png",menu->getNumberOfPlayers(), array);
                delete menu;
                currentClass = CurrentClass::game;
            }
            else if (menu->getMenuState() == MenuState::closing)
            {
                window.close();
            }
        }
        else if (currentClass == CurrentClass::game)
        {
            gameWorld->draw(window, deltaTime.asSeconds());

            if (gameWorld->getGameState() == GameState::shuttingDown)
            {
                delete gameWorld;
                menu = new Menu(window.getSize());
                currentClass = CurrentClass::menu;
            }
        }
        window.display(); // End the current frame and display its contents on screen
    }

}
