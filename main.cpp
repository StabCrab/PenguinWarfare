#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameWorld.h"
enum class gameState{menu = 0, game, pause};

int main(int argc, char* argv[])
{
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    sf::RenderWindow window(sf::VideoMode(width, height),
                            "Penguin Warfare");

    window.setTitle("Penguin Warfare");

    Menu* menuScreen = new Menu(width, height);
    GameWorld* gameWorld;

    gameState state = gameState::menu;
    while (window.isOpen()) // While window is open
    {
        sf::Event event;
        while (window.pollEvent(event)) // We check for events
        {
            if (event.type == sf::Event::Closed) // Request for closing the window
                window.close();
            if (state == gameState::menu)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (menuScreen->keyPressedEvent(event.key.code))
                    {

                        case menuCode::startGame:
                        {
                            int weaponCount[WEAPONS_COUNT];
                            for (int i = 0; i < WEAPONS_COUNT; ++i)
                            {
                                weaponCount[i] = INT_MAX;
                            }
                            gameWorld = new GameWorld(window, "terrainB.png",2, weaponCount);
                            state = gameState::game;
                            delete menuScreen;
                            break;
                        }
                        case menuCode::goOn:
                        {
                            break;
                        }
                        case menuCode::close:
                        {
                            window.close();
                            break;
                        }
                    }
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    menuScreen->keyReleasedEvent(event.key.code);
                }
            }
            else if (state == gameState::game)
            {
                if (event.type == sf::Event::KeyPressed)
                {
                    gameWorld->keyPressedEvent(event.key.code);
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    gameWorld->keyReleasedEvent(event.key.code);
                }
            }
            else if (state == gameState::pause)
            {

            }

        }
        window.clear(sf::Color(150,150,150)); // Clear the whole window before rendering a new frame
        if (state == gameState::menu)
            menuScreen->draw(window);
        else if (state ==gameState::game)
            gameWorld->draw(window);

        window.display(); // End the current frame and display its contents on screen

    }

}
