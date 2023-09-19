#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include"EditorState.h"
#include "Button.h"


class MainMenuState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    

    std::map<std::string, Button*> buttons;

    //Functions
    void initVariables();
    void initBackGround();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif

