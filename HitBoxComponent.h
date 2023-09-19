#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

#include<iostream>
#include<ctime>
#include<cstdlib>

#include"SFML/Graphics.hpp"
#include"SFML/Network.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"

class HitBoxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;

public:
	HitBoxComponent(sf::Sprite&sprite,float offeset_x,float offset_y,float width,float height);
	virtual ~HitBoxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};
#endif
