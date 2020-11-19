//
// Created by trykr on 22.10.2020.
//

#ifndef PENGUINWARFARE_MENU_H
#define PENGUINWARFARE_MENU_H
#include <SFML/Graphics.hpp>

#define NUMBER_OF_ITEMS 3
enum class menuCode
{
    startGame = 0,
    goOn,
    close
};
class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow& window);

    void moveUp(bool isDone);
    void moveDown(bool isDone);

    unsigned int getSelectedItemIndex();

    menuCode keyPressedEvent(sf::Keyboard::Key);
    void keyReleasedEvent(sf::Keyboard::Key);

    void runMenu(sf::RenderWindow& window); //For now we can do it only from main TODO: Think how to get to menu from GameWorld

private:
    bool isDone = false;
    unsigned int selectedItemIndex;
    sf::Font font;
    sf::Text menuItems[NUMBER_OF_ITEMS];
};


#endif //PENGUINWARFARE_MENU_H
