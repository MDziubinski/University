#include "End.h"

End::End(std::shared_ptr<Content>&Content) : s_Content(Content), End_Replay_Button_Pressed(false), End_Exit_Button_Pressed(false), End_MainMenu_Button_Pressed(false)
{
}

End::~End()
{
}

void End::Initialize()
{
	s_Content->s_Assets->Add_Texture("Assets/Textures/spacev2.png", BACKGROUND);
	Background.setTexture(s_Content->s_Assets->Get_Texture(BACKGROUND));
	Background.setPosition(0, 0);

	Score_Text.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	Score_Text.setString("Final Score: " + std::to_string(s_Content->s_File->score));
	Score_Text.setCharacterSize(20);
	Score_Text.setOutlineColor(sf::Color::Black);
	Score_Text.setOutlineThickness(2);
	Score_Text.setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * Score_Text.getGlobalBounds().width, s_Content->s_Window->getSize().y / 2 - 50.f);
	
	
	options[0].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	options[0].setString("Replay");
	options[0].setCharacterSize(20);
	options[0].setOutlineColor(sf::Color::Black);
	options[0].setOutlineThickness(2);
	options[0].setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * options[0].getGlobalBounds().width, s_Content->s_Window->getSize().y / 2);
	

	options[1].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	options[1].setString("Main Menu");
	options[1].setCharacterSize(20);
	options[1].setOutlineColor(sf::Color::Black);
	options[1].setOutlineThickness(2);
	options[1].setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * options[1].getGlobalBounds().width, s_Content->s_Window->getSize().y / 2 + 25.f);
	

	options[2].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	options[2].setString("Exit");
	options[2].setCharacterSize(20);
	options[2].setOutlineColor(sf::Color::Black);
	options[2].setOutlineThickness(2);
	options[2].setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * options[2].getGlobalBounds().width, s_Content->s_Window->getSize().y / 2 + 50.f);
	
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
			case sf::Keyboard::Up:
			{
				if (selected_index - 1 >= 0)
				{
					options[selected_index].setFillColor(sf::Color::White);
					selected_index--;
					options[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
			}
			case sf::Keyboard::W:
			{
				if (selected_index - 1 >= 0)
				{
					options[selected_index].setFillColor(sf::Color::White);
					selected_index--;
					options[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (selected_index + 1 < 3)
				{
					options[selected_index].setFillColor(sf::Color::White);
					selected_index++;
					options[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
			}
			case sf::Keyboard::S:
			{
				if (selected_index + 1 < 3)
				{
					options[selected_index].setFillColor(sf::Color::White);
					selected_index++;
					options[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				End_Replay_Button_Pressed = false;
				End_Exit_Button_Pressed = false;
				End_MainMenu_Button_Pressed = false;
				if (selected_index == 0)
				{
					End_Replay_Button_Pressed = true;
				}
				if (selected_index == 1)
				{
					End_MainMenu_Button_Pressed = true;
				}
				if (selected_index == 2)
				{
					End_Exit_Button_Pressed = true;
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

	if (End_Replay_Button_Pressed)
	{
		s_Content->s_File->score = 0;
		s_Content->s_States->PutOnStack(std::make_unique<Play>(s_Content), true);
	}
	else if (End_Exit_Button_Pressed)
	{
		s_Content->s_File->Sort_Results();
		s_Content->s_File->Write_File();
		s_Content->s_Window->close();
	}
	else if (End_MainMenu_Button_Pressed)
	{
		s_Content->s_File->Sort_Results();
		s_Content->s_File->Write_File();
		s_Content->s_File->score = 0;
		s_Content->s_States->PutOnStack(std::make_unique<MainMenu>(s_Content), true);
	}
}

void End::Draw()
{
	s_Content->s_Window->clear();
	s_Content->s_Window->draw(Background);
	s_Content->s_Window->draw(Score_Text);
	for (int i = 0; i < 3; i++)
	{
		s_Content->s_Window->draw(options[i]);
	}
	s_Content->s_Window->display();
}