#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include"SettingsState.h"
#include"EditorState.h"
#include "Gui.h"


class MainMenuState :
    public State
{
private:
    //Variables
 
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Font font;
    

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif

