#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:
    //Variables
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //Functions
    void initVariables();
    void initBackGround();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void renderButtons(sf::RenderTarget* target = NULL);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif

