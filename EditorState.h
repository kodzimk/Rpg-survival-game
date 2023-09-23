#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include"PauseMenu.h"
#include"TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
    //Variables
    sf::View view;
    float cameraSpeed;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape sidebar;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;



    bool collision;
    short type;


    //Functions
    void initView();
    void initVariables();
    void initBackGround();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initGui();
    void initButtons();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);

    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void updatePauseMenuButtons();
};
#endif

