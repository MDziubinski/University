#include "End.h"
#include "Play.h"
#include <SFML/Window/Event.hpp>

End::End(std::shared_ptr<Content>& Content) : s_Content(Content), Replay_Button_Selected(true), Replay_Button_Pressed(false), Exit_Button_Selected(false), Exit_Button_Pressed(false)
{
}

End::~End()
{
	std::cout << "End destructor!" << std::endl;
}

void End::Initialize()
{


	Replay_Button.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	Replay_Button.setString("Replay");
	Replay_Button.setOrigin(Replay_Button.getLocalBounds().width / 2, Replay_Button.getLocalBounds().height / 2);
	Replay_Button.setPosition(s_Content->s_Window->getSize().x / 2 + 14, s_Content->s_Window->getSize().y / 2);
	Replay_Button.setCharacterSize(20);


	Exit_Button.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	Exit_Button.setString("Exit");
	Exit_Button.setOrigin(Exit_Button.getLocalBounds().width / 2, Exit_Button.getLocalBounds().height / 2);
	Exit_Button.setPosition(s_Content->s_Window->getSize().x / 2 + 14, s_Content->s_Window->getSize().y / 2 + 25.f);
	Exit_Button.setCharacterSize(20);

}

void End::Input_Processing()
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
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
			{
				s_Content->s_Window->close();
			}
			case sf::Keyboard::Up:
			{
				if (!Replay_Button_Selected)
				{
					Replay_Button_Selected = true;
					Exit_Button_Selected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!Exit_Button_Selected)
				{
					Replay_Button_Selected = false;
					Exit_Button_Selected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				Replay_Button_Pressed = false;
				Exit_Button_Pressed = false;
				if (Replay_Button_Selected)
				{
					Replay_Button_Pressed = true;
				}
				else
				{
					Exit_Button_Pressed = true;
				}

				break;
			}
			default:
			{
				break;
			}
			}
		}

	}
}

void End::Update()
{
	if (Replay_Button_Selected)
	{
		Replay_Button.setFillColor(sf::Color::Black);
		Exit_Button.setFillColor(sf::Color::White);
	}
	else
	{
		Exit_Button.setFillColor(sf::Color::Black);
		Replay_Button.setFillColor(sf::Color::White);
	}

	if (Replay_Button_Pressed)

	{
		Replay_Button.setFillColor(sf::Color::Yellow);
		s_Content->s_States->PutOnStack(std::make_unique<Play>(s_Content), true);
	}
	else if (Exit_Button_Pressed)
	{
		Exit_Button.setFillColor(sf::Color::Yellow);
		s_Content->s_Window->close();
	}
}

void End::Draw()
{
	s_Content->s_Window->clear(sf::Color::Green);
	s_Content->s_Window->draw(Replay_Button);
	s_Content->s_Window->draw(Exit_Button);
	s_Content->s_Window->display();
}