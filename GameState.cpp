#include"stdafx.h"
#include "GameState.h"

//Initializer functions
void GameState::initDeferrefRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width
		, this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(0, 0, 
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height)
	);

	this->view.setCenter(
		sf::Vector2f(
			this->stateData->gfxSettings->resolution.width  / 2.f,
			this->stateData->gfxSettings->resolution.height / 2.f)
	);
}

void GameState::initKeybinds()
{

	std::ifstream ifs("Config/gamestate_keybinds.ini.txt");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

}


void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROF:MAINEMNUSTATE COULDNOT LOAD FONT ");
	}
}



void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET2.png"))
	{
		throw "ERROR GAMESTATE COULD NOT LOAD TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.f,vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "QUIT");
}

void GameState::initPlayers()
{
	this->player = new Player(0,0,this->textures["PLAYER_SHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player,this->stateData->gfxSettings->resolution);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100,
		"Resources/Images/Tiles/tilesheet3.png");
	this->tileMap->loadFromFile("text.txt");
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferrefRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
	delete this->playerGUI;
}

//Functions
void GameState::updateView(const float& dt)
{
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width /2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f));

	if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
	{
		this->view.setCenter(0.f +this->view.getSize().x / 2.f, this->view.getCenter().y);
	}
	else if (this->view.getCenter().x + this->view.getSize().x / 2.f > 3000.f)
	{
		this->view.setCenter(3000.f - this->view.getSize().x / 2.f, this->view.getCenter().y);
	}
	if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
	{
		this->view.setCenter(this->view.getCenter().y, 0.f+ this->view.getSize().y / 2.f);
	}
	else if (this->view.getCenter().y + this->view.getSize().y / 2.f > 3000.f)
	{
		this->view.setCenter(this->view.getCenter().x,  3000.f - this->view.getSize().y /2.f);
	}
}

void GameState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonsPressed("QUIT"))
		this->endState();
}

void GameState::updatePlayerInput(const float& dt)
{

	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move( -1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move( 1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0, -1.f, dt);

		if (this->getKeytime())
			this->player->gainEXP(1);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0, 1.f, dt);

		if(this->getKeytime())
		   this->player->loseEXP(1);
	}

}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->player,dt);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt);

		this->playerGUI->update(dt);

	}
	else
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePausedMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture,this->player->getGridPosition(static_cast<int>(this->stateData->gridSize)),	
		false);

	this->player->render(this->renderTexture,false);

	this->tileMap->renderDeferred(this->renderTexture);

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);
	
		if(this->paused)
		{
			this->renderTexture.setView(this->renderTexture.getDefaultView());
			this->pmenu->render(this->renderTexture);
		}

	this->renderTexture.display();
		/*this->renderSprite.setTexture(this->renderTexture.getTexture());*/
		target->draw(this->renderSprite);
}
