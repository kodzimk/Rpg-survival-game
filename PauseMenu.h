#ifndef  PAUSEMENU_H
#define PAUSEMENU_H

#include<cstdlib>
#include<iostream>
#include<string>
#include<map>
#include<math.h>

#include"SFML/Graphics.hpp"
#include"SFML/Network.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Gui.h"

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
	PauseMenu(sf::RenderWindow& window,sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonsPressed(const std::string key) ;
	void addButton(const std::string key,float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};
#endif

