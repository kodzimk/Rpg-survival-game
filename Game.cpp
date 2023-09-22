#include"stdafx.h"
#include "Game.h"

//Static functions

//Initializer functions
void Game::initVariables()
{
	this->window = NULL;

	this->dt = 0.f;

	this->gridSize = 50.f;
}

void Game::initGraphicsSettings()
{
	this->gfSettings.loadFromFile("Config/graphics.ini.txt");
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}


void Game::initWindow()
{
	if(this->gfSettings.fullscreen)
	  this->window = new sf::RenderWindow(
		  this->gfSettings.resolution,this->gfSettings.title,
		  sf::Style::Fullscreen,this->gfSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(this->gfSettings.resolution, this->gfSettings.title, 
			sf::Style::Titlebar| sf::Style::Close, this->gfSettings.contextSettings);

	this->window->setFramerateLimit(this->gfSettings.framRateLimit);
	this->window->setVerticalSyncEnabled(this->gfSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supportedKeys.ini.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();

}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window,this->gfSettings,&this->supportedKeys,&this->states));
}

//Constructor Destructur
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::endApplication()
{
	std::cout << "Endging Application" << "\n";
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::updateDt()  
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
	
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
	{
		this->states.top()->render();
	}
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}
