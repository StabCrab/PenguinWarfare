//
// Created by trykr on 22.10.2020.
//

#include <iostream>
#include "Menu.h"

Menu::Menu(sf::Vector2u windowSize)
{
    menuItems = new sf::Text[NUMBER_OF_ITEMS];
    startGameItems = new sf::Text[NUMBER_OF_START_GAME_ITEMS];
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Cannot find font"); //Throw exception if cannot find font
    }
    for (int i = 0; i < NUMBER_OF_ITEMS; ++i) //For each item set font, color and position
    {
        menuItems[i].setFont(font);
        menuItems[i].setFillColor(sf::Color::Black);
        menuItems[i].setPosition(100, windowSize.y / (NUMBER_OF_ITEMS + 1) * (i + 1));
    }
    selectedItemIndex = 0; // Current item = 0 on default
    menuItems[0].setFillColor(sf::Color::White); // Color of current item

    menuItems[0].setString("Play"); // Set string for items
    menuItems[1].setString("Options");
    menuItems[2].setString("Exit");

    for (int i = 0; i < NUMBER_OF_START_GAME_ITEMS; ++i)
    {
        startGameItems[i].setFont(font);
        startGameItems[i].setFillColor(sf::Color::Black);
        startGameItems[i].setPosition(100, windowSize.y / (NUMBER_OF_START_GAME_ITEMS + 1) * (i + 1));
    }

    startGameItems[0].setString("Play");
    startGameItems[1].setString("Number of teams " + std::to_string(numberOfTeams));
    startGameItems[2].setString("Choose the number of weapons (WIP)");
    startGameItems[3].setString("Choose map (WIP)");

    menuState = MenuState::generalMenu;
}

Menu::~Menu()
{
    delete [] menuItems;
    delete [] startGameItems;
}

void Menu::draw(sf::RenderWindow &window) //Here we just drawing menu in window
{
    switch (menuState)
    {
        case MenuState::generalMenu:
        {
            for (int i = 0; i < NUMBER_OF_ITEMS; i++)
            {
                window.draw(menuItems[i]);
            }
            break;
        }
        case MenuState::gameStartOptions:
        {
            for (int i = 0; i < NUMBER_OF_START_GAME_ITEMS; ++i)
            {
                window.draw(startGameItems[i]);
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void Menu::moveDown(bool isDone)
{
    if (isDone) // check if we go up or down once per press
        return;
    if (menuState == MenuState::generalMenu)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
        if (selectedItemIndex == NUMBER_OF_ITEMS - 1) // If we are in the bottom of the list
        {
            selectedItemIndex = 0; //we set active the top
        }
        else
            selectedItemIndex++; // else just go down
        menuItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
    }
    if (menuState == MenuState::gameStartOptions)
    {
        startGameItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
        if (selectedItemIndex == NUMBER_OF_START_GAME_ITEMS - 1) // If we are in the bottom of the list
        {
            selectedItemIndex = 0; //we set active the top
        }
        else
            selectedItemIndex++; // else just go down
        startGameItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
    }
}

void Menu::moveUp(bool isDone)
{
    if (isDone) // check if we go up or down once per press
        return;
    if (menuState == MenuState::generalMenu)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
        if (selectedItemIndex == 0) // If we are in the bottom of the list
        {
            selectedItemIndex = NUMBER_OF_ITEMS - 1; //we set active the top
        }
        else
            selectedItemIndex--; // else just go down
        menuItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
    }
    if (menuState == MenuState::gameStartOptions)
    {
        startGameItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
        if (selectedItemIndex == 0) // If we are in the bottom of the list
        {
            selectedItemIndex = NUMBER_OF_START_GAME_ITEMS - 1; //we set active the top
        }
        else
            selectedItemIndex--; // else just go down
        startGameItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
    }
}

unsigned int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}

void Menu::keyPressedEvent(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::S) //If it's S, we go down
    {
        moveDown(isDone);
        isDone = true; //set isDone flag true to be sure we do this once
    }
    if (key == sf::Keyboard::W) //If it's W, we go up
    {
        moveUp(isDone);
        isDone = true;
    }
    if (key == sf::Keyboard::A)
    {
        if (menuState == MenuState::gameStartOptions)
        {
            if (selectedItemIndex == 1)
            {
                numberOfTeams--;
                if (numberOfTeams == 1)
                    numberOfTeams = 4;
                startGameItems[selectedItemIndex].setString("Number of teams " + std::to_string(numberOfTeams));
            }
        }
    }
    if (key == sf::Keyboard::D)
    {
        if (menuState == MenuState::gameStartOptions)
        {
            if (selectedItemIndex == 1)
            {
                numberOfTeams++;
                if (numberOfTeams == 5)
                    numberOfTeams = 2;
                startGameItems[selectedItemIndex].setString("Number of teams " + std::to_string(numberOfTeams));
            }
        }
    }
    if (key == sf::Keyboard::Escape)
    {
        menuState = MenuState::generalMenu;
    }
}

void Menu::keyReleasedEvent(sf::Keyboard::Key key) // If we release key, we can move again
{
    isDone = false;
    if (key == sf::Keyboard::Enter)
    {
        if (menuState == MenuState::generalMenu)
        {
            switch (selectedItemIndex)
            {
                case 0: //Start the game TODO: I need to make some options of level here in the future
                {
                    menuState = MenuState::gameStartOptions;
                    startGameItems[selectedItemIndex].setFillColor(sf::Color::White);
                    break;
                }
                case 1: //Options (It's about the game, not about level)
                {
                    menuState = MenuState::options;
                    break;
                }
                case 2: // Exit
                {
                    menuState = MenuState::closing;
                    break;
                }
                default:
                {
                    throw std::runtime_error("Wrong selectedItemIndex");
                }
            }
        }
        else if (menuState == MenuState::gameStartOptions)
        {
            switch (selectedItemIndex)
            {
                case 0:
                {
                    menuState = MenuState::startingGame;
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

MenuState Menu::getMenuState() {
    return menuState;
}

unsigned int Menu::getNumberOfPlayers() {
    return numberOfTeams;
}
