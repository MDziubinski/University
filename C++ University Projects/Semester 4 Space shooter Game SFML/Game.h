#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "StateManager.h"
#include "AssetManager.h"
#include "FileManager.h"

enum Asset_ID
{
	MAIN_FONT = 0,
	SECONDARY_FONT = 1,
	BACKGROUND = 2,
	PLAYER = 3,
	BULLET = 4,
	ENEMY = 5,
	EN_BULLET = 6,
	BOSS = 7,
	BOSS_BULLET = 8,
	ASTEROID = 9,
	POWERUP = 10
};

struct Content
{
	//Pointer to access window functions
	std::unique_ptr<sf::RenderWindow> s_Window;

	//Pointer to access states functions
	std::unique_ptr<Engine::StateManager> s_States;

	//Pointer to access assets functions
	std::unique_ptr<Engine::AssetManager> s_Assets;

	//Pointer to access file functions
	std::unique_ptr<Engine::FileManager> s_File;

	Content()
	{
		s_Window = std::make_unique<sf::RenderWindow>();
		s_States = std::make_unique<Engine::StateManager>();
		s_Assets = std::make_unique<Engine::AssetManager>();
		s_File = std::make_unique<Engine::FileManager>();
	}
};


class Game
{
	std::shared_ptr<Content> s_Content; //Shared as the pointer will commonly used for all of the states;
public:
	Game();
	~Game();

	void Run(); //Function starting whole game
};
