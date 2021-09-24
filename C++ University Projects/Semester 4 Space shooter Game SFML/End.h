#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
#include "State.h"
#include "Play.h"
#include "Game.h"
#include "MainMenu.h"

class End : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text Replay_Button;
	sf::Text Exit_Button;
	sf::Text Score_Text;
	sf::Text MainMenu_Button;
	sf::Sprite Background;

	bool End_Exit_Button_Pressed;
	bool End_Replay_Button_Pressed;
	bool End_MainMenu_Button_Pressed;

	int selected_index = 0;
	sf::Text options[3];

public:
	End(std::shared_ptr<Content>& content);
	~End();

	void Initialize(); //Initailizing and setting all fonts and word
	void Input_Processing(); //Processing and handling inputs
	void Update(); //Updating state
	void Draw(); //Drawing on screen menu options and game title
};