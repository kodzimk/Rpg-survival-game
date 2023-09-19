#ifndef  ENTITY_H
#define  ENTITY_H

#include"MovementComponent.h"
#include"AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();


	//Component Functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity,float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void setPosition(const float x, const float y);

	virtual void move(const float x,const float y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
	
};
#endif

