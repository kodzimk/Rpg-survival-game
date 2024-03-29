#ifndef  PAUSEMENU_H
#define PAUSEMENU_H

#include"Gui.h"

class Gui;

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

	//Private functions
	

public:
	PauseMenu(sf::VideoMode& window,sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonsPressed(const std::string key) ;
	void addButton(const std::string key,float y, const float width, const float height,const unsigned charSize, const std::string text);
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);
};
#endif

