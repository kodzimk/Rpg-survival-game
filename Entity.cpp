#include"stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitBoxComponent(sf::Sprite& sprite,float offset_x,float offset_y,float width,float height)
{
	this->hitboxComponent = new HitBoxComponent(sprite,offset_x, offset_y, width,height);
}

void Entity::createMovementComponent(const float maxVelocity,float acceleration,float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	   return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + sf::Vector2f(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height/2.f 
		);

	return this->sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f,
		this->sprite.getGlobalBounds().height / 2.f);
}

const sf::FloatRect Entity::getNextPositionsBounds(const float& dt)
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity()*dt);

	return sf::FloatRect(-1.f,-1.f,-1.f,-1.f);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeu) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) /gridSizeu,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeu
		);

	return	 sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeu,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeu
	);;
}

const sf::FloatRect Entity::getGloabalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	if(this->hitboxComponent)
		this->hitboxComponent->setPosition(x,y);
	else
	   this->sprite.setPosition(x,y);	
}


void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->move(dir_x, dir_y, dt);
	
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target, const bool show_hitbox)
{
		target.draw(this->sprite);

		if (this->hitboxComponent)
			this->hitboxComponent->render(target);

}


