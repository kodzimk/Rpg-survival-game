#pragma once
class AttributeComponent
{
public:
	//Lvelings
	int level;
	int exp;
	int expNext;
	int attributePoints;


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
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void loseEXP(const int exp);
	void gainExp(const int xp);

	void updateLevel();
	void updateStates(const bool reset);

	void update();

};

