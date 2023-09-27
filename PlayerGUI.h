#pragma once

#include"Player.h"
#include"Gui.h"

class Gui;
class Player;
class RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;
	sf::VideoMode& vm;


	std::string levelBarString;
	sf::Text levelBarText;
	sf::RectangleShape levelBarBack;


	
	
	gui::ProgressBar* expBar;


	gui::ProgressBar* hpBar;


	void initFont();
	void initLevelBar();
	void initHPBar();
	void initEXPBar();

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	virtual ~PlayerGUI();

	//Functions
	void updateLevelBar();
	void updateEXPBar();
	void updateHPBar();
	void update(const float& dt);

	void renderLevelBar(sf::RenderTarget& target);
	void renderEXPBar(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

