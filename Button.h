#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sstream>

#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

enum button_states{BTN_IDLE = 0,BTN_HOVER,BTN_ACTIVE};

class Button
{
private:
	short unsigned buttonState;


	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textidleColor;
	sf::Color textHoverColor;
	sf::Color textactiveColor;  

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x,float y,float width,float height,sf::Font* font,std::string 
		text, unsigned character_size, sf::Color text_idle_color,
		sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);
	 ~Button();

	 const bool isPressed() const;

	 //Functions
	 void update(const sf::Vector2f& mousePos);
	 void render(sf::RenderTarget& target);

};
#endif

