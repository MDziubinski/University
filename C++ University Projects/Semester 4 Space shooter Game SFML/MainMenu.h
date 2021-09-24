#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "State.h"
#include "Game.h"
#include "Nick.h"


class MainMenu : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text Game_Title;
	sf::Sprite Background;

	bool Play_Button_Pressed;
	bool Exit_Button_Pressed;
	bool LeaderBoards_Button_Pressed;
	

	int selected_index = 0;
	sf::Text menu[3];

public:
	MainMenu(std::shared_ptr<Content>& Content);
	~MainMenu();

	void Initialize();  //Initailizing and setting all fonts and words
	void Input_Processing(); //Processing and handling inputs
	void Update(); //Updating state
	void Draw();  //Drawing on screen menu options and game title
};