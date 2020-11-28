//
// Created by trykr on 22.10.2020.
//

#ifndef PENGUINWARFARE_MENU_H
#define PENGUINWARFARE_MENU_H
#include <SFML/Graphics.hpp>

#define NUMBER_OF_ITEMS 3
#define NUMBER_OF_START_GAME_ITEMS 4
enum class MenuState
{
    generalMenu = 0,
    gameStartOptions,
    startingGame,
    options,
    closing,
};
class Menu {
public:
    Menu(sf::Vector2u windowSize);
    ~Menu();

    void draw(sf::RenderWindow& window);

    void moveUp(bool isDone);
    void moveDown(bool isDone);

    unsigned int getSelectedItemIndex();

    void keyPressedEvent(sf::Keyboard::Key key);
    void keyReleasedEvent(sf::Keyboard::Key key);

    MenuState getMenuState();

    unsigned int getNumberOfPlayers();

private:
    bool isDone = false;
    unsigned int selectedItemIndex;
    sf::Font font;
    sf::Text* menuItems;
    sf::Text* startGameItems;
    MenuState menuState;
    unsigned int numberOfTeams = 2;
};


#endif //PENGUINWARFARE_MENU_H
