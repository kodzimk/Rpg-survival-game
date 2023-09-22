#ifndef GAME_H
#define GAME_H

#include"MainMenuState.h"

class Game
{
private:
	

    //Variables
	GraphicsSettings gfSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	float gridSize;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

    //Initialitaion
	void initVariables();
	void initGraphicsSettings();
	void initStateData();
	void initWindow();
	void initKeys();
	void initStates();

public:
	Game();
	virtual ~Game();

	//Regurular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};
#endif
