#include "stdafx.h"
#include "PlayerGUI.h"

//Initializer
void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Dosis-Light.ttf");
}

void PlayerGUI::initHPBar()
{

	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;

	this->hpBarMaxWidth = width;



	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50,50,50,200));
	this->hpBarBack.setPosition(x,y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(x,y);

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(16);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
}

void PlayerGUI::initEXPBar()
{
	float width = 200.f;
	float height = 20.f;
	float x = 20.f;
	float y = 80.f;

	this->expBarMaxWidth = width;



	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(20, 250, 20, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(14);
	this->expBarText.setPosition(this->expBarInner.getPosition().x + 10.f, this->expBarInner.getPosition().y + 5.f);
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();
	this->initEXPBar();
	this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{

}



void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInner.setSize(sf::Vector2f(static_cast<float>(
		std::floor(this->hpBarMaxWidth * percent)),
		this->hpBarInner.getSize().y));


	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + "/" + std::to_string(this->player->getAttributeComponent()->expNext);
	
	this->expBarText.setString(this->expBarString);
}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);
	
	this->hpBarInner.setSize(sf::Vector2f(static_cast<float>(
		std::floor(this->hpBarMaxWidth * percent)),
		this->hpBarInner.getSize().y));


	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + "/" + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderEXPBar(target);
	this->renderHPBar(target);
}
