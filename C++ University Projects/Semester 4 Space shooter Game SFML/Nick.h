#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include <memory>
#include <array>
#include "State.h"
#include "Game.h"

class Nick : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text text;
	sf::Sprite Background;

	sf::String playerInput;
	sf::Text PlayerNick;	
	std::string playerNick;
	bool Nick_Exit_Button_Pressed;
	bool Nick_Play_Button_Pressed;
public:
	Nick(std::shared_ptr<Content>& content);
	~Nick();

	void Initialize();
	void Input_Processing();
	void Update();
	void Draw();

	void Pause();
	void Start();

};