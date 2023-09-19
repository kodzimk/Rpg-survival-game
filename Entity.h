#ifndef  ENTITY_H
#define  ENTITY_H


#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<stack>
#include<vector>
#include<map>

#include"SFML/Graphics.hpp"
#include"SFML/Network.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"


class Entity
{
private:
	void initVariables();

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;

	float movementSpeed;


public:
	Entity();
	virtual ~Entity();
	//Component Functions
	void createSprite(sf::Texture* texture);


	//Functions
	
	virtual void move(const float& dt,const float x,const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	
};
#endif

