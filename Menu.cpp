//
// Created by trykr on 22.10.2020.
//

#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("Cannot find font"); //Throw exception if cannot find font
    }
    for (int i = 0; i < NUMBER_OF_ITEMS; i++) //For each item set font, color and position
    {
        menuItems[i].setFont(font);
        menuItems[i].setFillColor(sf::Color::Black);
        menuItems[i].setPosition(100, height / (NUMBER_OF_ITEMS + 1) * (i + 1));
    }
    selectedItemIndex = 0; // Current item = 0 on default
    menuItems[0].setFillColor(sf::Color::White); // Color of current item

    menuItems[0].setString("Play"); // Set string for items
    menuItems[1].setString("Options");
    menuItems[2].setString("Exit");

}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window) //Here we just drawing menu in window
{
    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        window.draw(menuItems[i]);
    }
}

void Menu::moveDown(bool isDone)
{
    if (isDone) // check if we go up or down once per press
        return;
    menuItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
    if (selectedItemIndex == NUMBER_OF_ITEMS - 1) // If we are in the bottom of the list
    {
        selectedItemIndex = 0; //we set active the top
    }
    else
        selectedItemIndex++; // else just go down
    menuItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
}

void Menu::moveUp(bool isDone)
{
    if (isDone) // check if we go up or down once per press
        return;
    menuItems[selectedItemIndex].setFillColor(sf::Color::Black); //Set current item black(because now it is not active)
    if (selectedItemIndex == 0) // If we are in the bottom of the list
    {
        selectedItemIndex = NUMBER_OF_ITEMS - 1; //we set active the top
    }
    else
        selectedItemIndex--; // else just go down
    menuItems[selectedItemIndex].setFillColor(sf::Color::White); //Set new current item white(because now it is active)
}

void Menu::runMenu(sf::RenderWindow& window)
{

}

unsigned int Menu::getSelectedItemIndex() {
    return selectedItemIndex;
}

menuCode Menu::keyPressedEvent(sf::Keyboard::Key key)
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
    if (key == sf::Keyboard::Enter)
    {
        switch (selectedItemIndex)
        {
            case 0: //Start the game TODO: I need to make some options of level here in the future
            {
                return menuCode::startGame;
            }
            case 1: //Options (It's about the game, not about level)
            {
                return menuCode::goOn;
            }
            case 2: // Exit
            {
                return menuCode::close;
            }
            default:
            {
                throw std::runtime_error("Wrong selectedItemIndex");
            }
        }
    }
}

void Menu::keyReleasedEvent(sf::Keyboard::Key) // If we release key, we can move again
{
    isDone = false;
}
