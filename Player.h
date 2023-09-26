#ifndef PLAYER_H
#define PLAYER_H

#include"Entity.h"

class Entity;

class Player:public Entity
{
private:
	//Variables
	bool attacking;
	sf::Sprite weapon_sprite;
	sf::Texture weapon_texture;


	//Initialzier functions
	void initVariables();
	void initComponents();
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

