#include "GameState.h"

void GameState::initKeybinds()
{
	this->keybinds.emplace("MOVE_LEFT",this->supportedKeys->at("A"));
	this->keybinds.emplace("MOVE_RIGHT", this->supportedKeys->at("D"));
	this->keybinds.emplace("MOVE_UP", this->supportedKeys->at("W"));
	this->keybinds.emplace("MOVE_DOWN", this->supportedKeys->at("S"));
}

GameState::GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys)
	: State(window,supportedKeys)
{
	this->initKeybinds();
}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "Ending GameSttae" << "\n";
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player.move(dt, 0, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player.move(dt, 0, 1.f);

}

void GameState::update(const float& dt)
{
	this->updateInput(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target )
{
	if (!target)
		target = this->window;

		this->player.render(target);
	
}
