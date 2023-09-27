#include"stdafx.h"
#include "Player.h"

//Initializer function
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

//Constructor Destcrutor
Player::Player(float x,float y,sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();

	this->setPosition(x, y);

	this->createHitBoxComponent(this->sprite,10.f,10.f,40.f,55.f);
	this->createMovementComponent(200.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponenet();
	std::cout<<this->skillComponent->getSkill("health")<<std::endl;

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0,64,64);
	this->animationComponent->addAnimation("WALK_DOWN", 12.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 12.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 12.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 12.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 12.f, 0, 2, 1,2,64 * 2,64);



}

Player::~Player() {

}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}



//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);


}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimations(const float& dt)
{

	if (this->attacking)
	{
		
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAttack();
	this->updateAnimations(dt);

	this->hitboxComponent->update();

	this->sword.update(mouse_pos_view, this->getCenter());

}

void Player::render(sf::RenderTarget& target,const bool show_hitbox)
{
   target.draw(this->sprite);
   this->sword.render(target);

	if(show_hitbox)
	this->hitboxComponent->render(target);
}
