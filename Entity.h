#ifndef  ENTITY_H
#define  ENTITY_H

#include"MovementComponent.h"
#include"AnimationComponent.h"
#include"HitBoxComponent.h"
#include"AttributeComponent.h"

class HitBoxComponent;
class AnimationComponent;
class MovementComponent;
class AttributeComponent;

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	HitBoxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;

public:
	Entity();
	virtual ~Entity();


	//Component Functions
	void setTexture(sf::Texture& texture);
	void createHitBoxComponent(sf::Sprite& sprite,const float offset_x,const float offset_y,float width,float height);
	void createMovementComponent(const float maxVelocity,float acceleration, float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	//Accesors
	virtual const sf::Vector2f& getPosition()const;
	virtual const sf::Vector2f getCenter()const;
	virtual const sf::FloatRect getNextPositionsBounds(const float& dt);
	virtual const sf::Vector2i getGridPosition(const int gridSizeu)const;
	virtual const sf::FloatRect getGloabalBounds()const;

	//Modifiers

	//Functions
	virtual void setPosition(const float x, const float y);

	virtual void move(const float x,const float y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target,const bool show_hitox) = 0;
	
};
#endif

