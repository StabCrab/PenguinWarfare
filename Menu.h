//
// Created by trykr on 22.10.2020.
//

#ifndef PENGUINWARFARE_MENU_H
#define PENGUINWARFARE_MENU_H
#include <SFML/Graphics.hpp>

#define NUMBER_OF_ITEMS 3
#define NUMBER_OF_START_GAME_ITEMS 4
#define NUMBER_OF_OPTIONS_ITEMS 1
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
    Menu(sf::RenderWindow& window, bool isFullscreen);
    ~Menu();

    void draw(sf::RenderWindow& window);

    void moveUp(bool isDone);
    void moveDown(bool isDone);

    unsigned int getSelectedItemIndex();

    bool getIsChangingStyle();

    void setIsChanginsStyleFalse();

    void keyPressedEvent(sf::Keyboard::Key key);
    void keyReleasedEvent(sf::Keyboard::Key key);

    MenuState getMenuState();

    void setMenuState(MenuState state);

    unsigned int getNumberOfPlayers() const;

private:
    bool isChangingStyle;
    bool isDone;
    unsigned int selectedItemIndex;
    sf::Font font;
    sf::Text menuItems[NUMBER_OF_ITEMS];
    sf::Text startGameItems[NUMBER_OF_START_GAME_ITEMS];
    sf::Text optionsItems[NUMBER_OF_OPTIONS_ITEMS];
    MenuState menuState;
    unsigned int numberOfTeams;
    sf::View view;
};


#endif //PENGUINWARFARE_MENU_H
