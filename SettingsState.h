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
    std::map<std::string, gui::DropDownList*> dropdownList;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    //Accessors

    //Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void renderGui(sf::RenderTarget& target);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif
