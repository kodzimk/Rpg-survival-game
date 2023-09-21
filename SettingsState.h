#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
    public State
{
private:
    //Variables
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;


    std::map<std::string, gui::Button*> buttons;

    gui::DropDownList* ddl;

    //Functions
    void initVariables();
    void initBackGround();
    void initFonts();
    void initKeybinds();
    void initButtons();
public:
    SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~SettingsState();

    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif
