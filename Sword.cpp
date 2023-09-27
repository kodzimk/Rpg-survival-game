#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	this->weapon_texture.loadFromFile("Resources/Images/Sprites/Player/sword.png");
	this->weapon_sprite.setTexture(this->weapon_texture);

	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height);
}

Sword::~Sword()
{
}

void Sword::update(const sf::Vector2f mouse_pos_view,const sf::Vector2f center)
{
	this->weapon_sprite.setPosition(center);

	float dx = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	float deg = atan2(dY, dx) * 180 / 3.14;

	this->weapon_sprite.setRotation(deg + 90.f);
}
void Sword::render(sf::RenderTarget& target)
{
	target.draw(this->weapon_sprite);
}

