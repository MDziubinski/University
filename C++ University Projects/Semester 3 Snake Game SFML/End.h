#pragma once
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "Game.h"
#include <memory>

class End : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text Replay_Button;
	sf::Text Exit_Button;
	

	bool Replay_Button_Selected;
	bool Replay_Button_Pressed;
	bool Exit_Button_Selected;
	bool Exit_Button_Pressed;

public:
	End(std::shared_ptr<Content>& Content);
	~End();

	void Initialize();
	void Input_Processing();
	void Update();
	void Draw();
};

