#ifndef GAME_H
#define GAME_H

#include"GameState.h"
#include"MainMenuState.h"


class Game
{
private:
    //Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

    //Initialitaion
	void initVariables();
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
