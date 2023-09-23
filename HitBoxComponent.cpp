#include"stdafx.h"
#include "HitBoxComponent.h"

HitBoxComponent::HitBoxComponent(sf::Sprite& sprite, float offeset_x, 
	float offset_y,float width, float height)
	:sprite(sprite),offsetX(offeset_x),offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x +offeset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitBoxComponent::~HitBoxComponent()
{

}

const sf::Vector2f& HitBoxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

void HitBoxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitBoxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x,y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

bool HitBoxComponent::intersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

const sf::FloatRect HitBoxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

void HitBoxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitBoxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
