#ifndef GAMESTATE_H
#define GAMESTATE_H


#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"
#include"PlayerGUI.h"

class PauseMenu;
class TileMap;
class Player;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
    public State
{
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Vector2i viewGridPosition;


    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    PlayerGUI* playerGUI;
    sf::Texture texture;

    TileMap* tileMap;

//Functions
    void initDeferrefRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initPlayerGUI();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updatePausedMenuButtons();
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updateInput(const float& dt);
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
};
#endif

