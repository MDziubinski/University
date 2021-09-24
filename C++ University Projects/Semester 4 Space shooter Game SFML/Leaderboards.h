#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "State.h"
#include "Game.h"
#include "MainMenu.h"
#include "FileManager.h"


class Leaderboards : public Engine::State
{
	std::shared_ptr<Content> s_Content;

	sf::Text leaderboard_text;
	sf::Text top_ten;
	sf::Text var_text;

	sf::Sprite Background;

	std::vector<std::pair<int, std::string>> players;
	std::vector<sf::Text> playerTexts;

	bool LeaderBoards_Exit_Button_Pressed;
	int var;
	float dist;

public:
	Leaderboards(std::shared_ptr<Content>& content);
	~Leaderboards();

	void Initialize(); //Initailizing and setting all fonts and words
	void Input_Processing(); //Processing and handling inputs
	void Update(); //Updating state
	void Draw(); //Drawing on screen menu options and game title

};