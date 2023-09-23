#ifndef PLAYER_H
#define PLAYER_H

#include"Entity.h"

class Player:public Entity
{
private:
	//Variables
	bool attacking;


	//Initialzier functions
	void initVariables();
	void initComponents();
public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	//Functions
	void updateAttack();
	void updateAnimations(const float& dt);
	 void update(const float& dt);
	 void render(sf::RenderTarget& target);
};
#endif

