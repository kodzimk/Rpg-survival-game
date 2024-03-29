#ifndef PLAYER_H
#define PLAYER_H

#include"Entity.h"
#include"Sword.h"

class Entity;
class Sword;

class Player:public Entity
{
private:
	//Variables
	bool attacking;
	Sword sword;


	//Initialzier functions
	void initVariables();
	void initComponents();
	void initAnimtions();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();


	//Accesors
	AttributeComponent* getAttributeComponent();

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	void updateAttack();
	void updateAnimations(const float& dt);
	 void update(const float& dt,sf::Vector2f& mousePis);
	 void render(sf::RenderTarget& targetm, const bool show_hitbox = false);
};
#endif

