#ifndef GUI_H
#define GUI_H

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<sstream>

#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

enum button_states{BTN_IDLE = 0,BTN_HOVER,BTN_ACTIVE};

namespace gui
{
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
		Button(float x, float y, float width, float height, sf::Font* font, std::string
			text, unsigned character_size, sf::Color text_idle_color,
			sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color);
		~Button();

		const bool isPressed() const;
		const std::string& getText() const;

		//Modifiers
		void setText(const std::string text);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);

	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;


	public:
		DropDownList(float x,float y,float width,float height,sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2f& mousePos,const float& dt);
		void render(sf::RenderTarget& target);
	};
}
#endif

