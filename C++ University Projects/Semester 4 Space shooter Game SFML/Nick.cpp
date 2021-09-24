#include "Leaderboards.h"
#include "Nick.h"
#include "MainMenu.h"
#include "Play.h"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Nick::Nick(std::shared_ptr<Content>& content)
	:s_Content(content), Nick_Exit_Button_Pressed(false), Nick_Play_Button_Pressed(false)
{

}
Nick::~Nick()
{
}

void Nick::Initialize()
{
	s_Content->s_Assets->Add_Texture("Assets/Textures/spacev2.png", BACKGROUND);
	Background.setTexture(s_Content->s_Assets->Get_Texture(BACKGROUND));
	Background.setPosition(0, 0);

	text.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	text.setString("Please enter your nick: ");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(s_Content->s_Window->getSize().x / 2, s_Content->s_Window->getSize().y / 2 - 100.f);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2);

	PlayerNick.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	PlayerNick.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	PlayerNick.setPosition(s_Content->s_Window->getSize().x / 2, s_Content->s_Window->getSize().y / 2 - 60.f);
	PlayerNick.setFillColor(sf::Color::White);
	PlayerNick.setOutlineColor(sf::Color::Black);
	PlayerNick.setOutlineThickness(2);
}
void Nick::Input_Processing()
{
	sf::Event event;
	while (s_Content->s_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			s_Content->s_Window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Nick_Exit_Button_Pressed = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				Nick_Play_Button_Pressed = true;
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode == '\b') 
			{
				playerInput.erase(playerInput.getSize()- 1, 1);
			}
			else 
			{
				playerInput += event.text.unicode;
			}
			PlayerNick.setString(playerInput);
			
		}
	}
}
void Nick::Update()
{
	if (Nick_Exit_Button_Pressed)
	{
		s_Content->s_States->PutOnStack(std::make_unique<MainMenu>(s_Content), true);
	}
	else if (Nick_Play_Button_Pressed)
	{
		playerNick = playerInput;
		s_Content->s_File->Nick = playerNick;
		s_Content->s_States->PutOnStack(std::make_unique<Play>(s_Content), true);
	}
}
void Nick::Draw()
{
	s_Content->s_Window->clear();
	s_Content->s_Window->draw(Background);
	s_Content->s_Window->draw(text);
	s_Content->s_Window->draw(PlayerNick);
	s_Content->s_Window->display();
}

void Nick::Pause() {}
void Nick::Start() {}