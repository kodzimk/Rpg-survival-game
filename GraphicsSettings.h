#ifndef GRAPHICSSETTINGS_H
#define GRAPHICSSETTINGS_H

class GraphicsSettings
{
public:
	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned framRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	GraphicsSettings();
	



	//Functions
	void saveToFile(const std::string path);

	void loadFromFile(const std::string path);
};
#endif