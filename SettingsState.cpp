#include"stdafx.h"
#include "SettingsState.h"

//Initializer functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
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

void SettingsState::initGui()
{
	this->buttons["BACK"] = new gui::Button(1500.f, 880.f, 250.f, 65.f, &this->font, "Back", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(1300.f, 880.f, 250.f, 65.f, &this->font, "Apply", 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropdownList["RESOLUTION"] = new gui::DropDownList(800, 400, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f,450.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255,255,255,200));

	this->optionsText.setString(
		"Resultion \n\nFullscreen\n\nVsync \n\nAntialiasing \n\n" 
	);
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackGround();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}
SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();

	for (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}

	auto it2 = this->dropdownList.begin();

	for (it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); it2++)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{


}

void SettingsState::updateGui(const float& dt)
{
	for (auto& it : buttons)
	{
		it.second->update(this->mousePosWindow);
	}


		if (this->buttons["BACK"]->isPressed())
		{
			this->endState();
		}

		if (this->buttons["APPLY"]->isPressed())
		{
			this->stateData->gfxSettings->resolution = this->modes[this->dropdownList["RESOLUTION"]->getActiveElemtnId()];
			
			this->window->create(this->stateData->gfxSettings->resolution,this->stateData->gfxSettings->title,sf::Style::Default );
		}

	for (auto& it : this->dropdownList)
	{
		it.second->update(this->mousePosWindow,dt);
	}
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this-> dropdownList)
	{
		it.second->render(target);
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui(dt);

}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;


	target->draw(this->background);

	this->renderGui(*target);
	target->draw(this->optionsText);
}


