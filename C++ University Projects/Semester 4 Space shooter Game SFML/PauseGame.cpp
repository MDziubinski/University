#include "End.h"
#include "Play.h"
#include "PauseGame.h"
#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Content>& Content) : s_Content(Content)
{
}

PauseGame::~PauseGame()
{

}

void PauseGame::Initialize()
{
	PauseText.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	PauseText.setString("Pause");
	PauseText.setOrigin(PauseText.getLocalBounds().width / 2, PauseText.getLocalBounds().height / 2);
	PauseText.setPosition(s_Content->s_Window->getSize().x / 2 + 14, s_Content->s_Window->getSize().y / 2);
	PauseText.setCharacterSize(20);
	PauseText.setOutlineColor(sf::Color::Black);
	PauseText.setOutlineThickness(2);
}

void PauseGame::Input_Processing()
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
				s_Content->s_States->PopOutStack();
			}
		}

	}
}

void PauseGame::Update()
{

}

void PauseGame::Draw()
{
	s_Content->s_Window->draw(PauseText);
	s_Content->s_Window->display();
}

void PauseGame::Pause() {}
void PauseGame::Start() {}