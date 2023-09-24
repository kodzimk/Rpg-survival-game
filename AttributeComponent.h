#pragma once
class AttributeComponent
{
public:
	//Lvelings
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;


	//Attributes
	int strength;
	int vitailty;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damagMax;
	int accuracy;
	int defence;
	int luck;

	//Constructor distructor
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions

	void gainExp(const unsigned xp);

	void updateLevel();
	void updateStates(const bool reset);

	void update();

};

