#pragma once
#include "StateManager.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

enum Asset_ID
{
	MAIN_FONT = 0,
	GRASS = 1,
	APPLE = 2,
	WALL = 3,
	SNAKE = 4
};

struct Content
{
	std::unique_ptr<sf::RenderWindow> s_Window;
	std::unique_ptr<Engine::StateManager> s_States;
	std::unique_ptr<Engine::AssetManager> s_Assets;

	Content()
	{
		s_Window = std::make_unique<sf::RenderWindow>();
		s_States = std::make_unique<Engine::StateManager>();
		s_Assets = std::make_unique<Engine::AssetManager>();
	}
};


class Game
{
	std::shared_ptr<Content> s_Content; //Shared as the pointer will commonly used for all of the states;
public:
	Game();
	~Game();

	void Run(); //Starting whole game
};

