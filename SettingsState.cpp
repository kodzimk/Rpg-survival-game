#include"stdafx.h"
#include "SettingsState.h"

//Initializer functions
void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
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
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;


	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height))
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/BackGrounds/bg1.png"))
	{
		throw"ERORR MAIN MENU TATE: FAILED LOAD BACKGROUND";
	}


	this->background.setTexture(&this->backgroundTexture);

	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(72.f,vm), gui::p2pY(81.5f,vm), gui::p2pX(13.f,vm), 
		gui::p2pY(6.f,vm), &this->font, "Back", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(gui::p2pX(68.f,vm), gui::p2pY(81.5f,vm),
		gui::p2pX(60.f,vm), gui::p2pY(6.f,vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropdownList["RESOLUTION"] = new gui::DropDownList(gui::p2pX(42.f,vm),
		gui::p2pY(42.f,vm), gui::p2pX(10.4f,vm), 
		gui::p2pY(4.5f,vm), font, modes_str.data(), modes_str.size());


	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f,vm), gui::p2pY(41.7f,vm)));
	this->optionsText.setCharacterSize(gui::calcCharSize(vm , 80));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resultion \n\nFullscreen\n\nVsync \n\nAntialiasing \n\n"
	);
}

void SettingsState::resetGui()
{
	auto it = this->buttons.begin();

	for  (it = this->buttons.begin(); it != this->buttons.end(); it++)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropdownList.begin();
	for (it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); it2++)
	{
		delete it2->second;
	}

	this->dropdownList.clear();

	this->initGui();
}


SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
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
		
			this->resetGui();
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


