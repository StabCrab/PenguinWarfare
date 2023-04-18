#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameWorld.h"
enum class CurrentClass{menu = 0, game, pause};

int main()
{
    sf::Clock clock;
    sf::Time deltaTime;
    unsigned int width = sf::VideoMode::getDesktopMode().width;
    unsigned int height = sf::VideoMode::getDesktopMode().height;

    bool isFullscreen = true;
    sf::RenderWindow window(sf::VideoMode(width, height),
                            "Penguin Warfare", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setTitle("Penguin Warfare");


    Menu* menu = new Menu(window, isFullscreen);
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
            if (menu->getIsChangingStyle())
            {
                isFullscreen = !isFullscreen;
                if (isFullscreen)
                {
                    window.create(sf::VideoMode(width, height),
                                            "Penguin Warfare", sf::Style::Fullscreen);
                }
                else
                {
                    window.create(sf::VideoMode(width, height),
                                            "Penguin Warfare");

                }
                window.setVerticalSyncEnabled(true);
                window.setTitle("Penguin Warfare");
                menu->setIsChanginsStyleFalse();
            }
            if (menu->getMenuState() == MenuState::generalMenu
            || menu->getMenuState() == MenuState::gameStartOptions
            || menu->getMenuState() ==MenuState::options)
            {
                menu->draw(window);
            }
            else if (menu->getMenuState() == MenuState::startingGame)
            {
                clock.restart();
                currentClass = CurrentClass::game;
                gameWorld = new GameWorld(window, "TerrainT.png",menu->getNumberOfPlayers());
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
                menu = new Menu(window, isFullscreen);
                currentClass = CurrentClass::menu;
            }
        }
        window.display(); // End the current frame and display its contents on screen
    }

}
