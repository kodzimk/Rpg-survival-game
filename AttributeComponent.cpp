#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50/3) * (pow(this->level + 1,3) - 6 * pow(this->level + 1,2)+ ((this->level +1) *17) - 12));
	this->attributePoints = 2;

	this->vitailty = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->updateLevel();
	this->updateStates(true);

}

AttributeComponent::~AttributeComponent()
{

}




//Functions
void AttributeComponent::gainExp(const int xp)
{
	this->exp += xp;

	this->updateLevel();
}

void AttributeComponent::updateLevel()
{
	while(this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level +1, 2) + ((this->level +1) * 17) - 12));
		++this->attributePoints;
	}
}
void AttributeComponent::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;

}

void AttributeComponent::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}

void AttributeComponent::loseEXP(const int exp)
{
		this->exp -= exp;
}


void AttributeComponent::updateStates(const bool reset)
{
	this->damagMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->hpMax = this->vitailty * 9 + this->vitailty +this->strength + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->accuracy = this->dexterity * 5 +this->dexterity / 2 + this->intelligence / 5;
	this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck = this->intelligence * 2 + this->intelligence / 5;


	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
