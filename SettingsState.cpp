#include "SettingsState.h"

void SettingsState::initVariables()
{

}

void SettingsState::initBackGround()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y))
	);
	if (!this->backgroundTexture.loadFromFile("Resources/Images/BackGrounds/bg1.png"))
	{
		throw"ERORR MAIN MENU TATE: FAILED LOAD BACKGROUND";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROF:MAINEMNUSTATE COULDNOT LOAD FONT ");
	}
}

void SettingsState::initKeybinds()
{

	std::ifstream ifs("Config/mainmenustates_keybinds.ini.txt");

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

void SettingsState::initButtons()
{
	this->buttons["EXIT_STATE"] = new gui::Button(300, 780, 250, 50, &this->font, "Quit", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string li[] = { "1312","23232","323","323","3232" };

	this->ddl = new gui::DropDownList(100,100,200,50,font,li,5);
}


SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window,supportedKeys,states)
{
	this->initVariables();
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}
SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
	delete this->ddl;
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{


}

void SettingsState::updateButtons()
{
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosView);
	}


	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

	this->ddl->update(this->mousePosView, dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);

	this->renderButtons(*target);

	this->ddl->render(*target);
}

