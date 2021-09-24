#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include <memory>
#include <array>
#include "State.h"
#include "Game.h"

class PauseGame : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text PauseText;
	//sf::Sprite Background;
	//sf::Text Replay_Button;
	//sf::Text Exit_Button;
	//sf::Sprite Background;


public:
	PauseGame(std::shared_ptr<Content>& content);
	~PauseGame();

	void Initialize();
	void Input_Processing();
	void Update();
	void Draw();

	void Pause();
	void Start();

};