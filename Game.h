#ifndef GAME_H
#define GAME_H

#include"GameState.h"
#include"MainMenuState.h"


class Game
{
private:
	class GraphicsSettings
	{
	public:
		GraphicsSettings()
		{
			this->title = "DEFAULT";
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = false;
			this->framRateLimit = 120;
			this->verticalSync = false;
			this->contextSettings.antialiasingLevel = 0;
			this->videoModes = sf::VideoMode::getFullscreenModes();

		}

		//Variables
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned framRateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoModes;


		//Functions
		void saveToFile(const std::string path)
		{
			std::ofstream ofs(path);


			if (ofs.is_open())
			{
				ofs <<this->title;
				ofs << this->resolution.width <<" "<< this->resolution.height;
				ofs << this->fullscreen;
				ofs << this->framRateLimit;
				ofs << this->verticalSync;
				ofs << this->contextSettings.antialiasingLevel;
			}
			ofs.close();
		}

		void loadFromFile(const std::string path)
		{
			std::ifstream ifs(path);


			if (ifs.is_open())
			{
				std::getline(ifs, this->title);
				ifs >> this->resolution.width >> this->resolution.height;
				ifs >> this->fullscreen;
				ifs >> this->framRateLimit;
				ifs >> this->verticalSync;
				ifs >> this->contextSettings.antialiasingLevel;
			}
			ifs.close();

		}
	};

    //Variables
	GraphicsSettings gfSettings;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

    //Initialitaion
	void initVariables();
	void initGraphicsSettings();
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
