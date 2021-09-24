#include "MainMenu.h"
#include "Play.h"
#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Content>& Content) : s_Content(Content), Play_Button_Pressed(false), Exit_Button_Pressed(false), LeaderBoards_Button_Pressed(false)
{
}

MainMenu::~MainMenu()
{
	std::cout << "Mainmenu destructor!" << std::endl;
}

void MainMenu::Initialize()
{
	s_Content->s_Assets->Add_Font("Assets/Font/SNAP____.TTF", MAIN_FONT);
	Game_Title.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	Game_Title.setString("Snake");
	Game_Title.setOrigin(Game_Title.getLocalBounds().width / 2, Game_Title.getLocalBounds().height / 2);
	Game_Title.setPosition(s_Content->s_Window->getSize().x / 2, s_Content->s_Window->getSize().y / 2 -100.f);
	Game_Title.setFillColor(sf::Color::Black);
	
	
	menu[0].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(s_Content->s_Window->getSize().x / 2 +14.f, s_Content->s_Window->getSize().y / 2);
	menu[0].setCharacterSize(20);

	menu[1].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	menu[1].setString("Leaderboards (not implemented)");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(s_Content->s_Window->getSize().x / 2 + 30.f, s_Content->s_Window->getSize().y / 2 + 25.f);
	menu[1].setCharacterSize(20);
	
	menu[2].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(s_Content->s_Window->getSize().x / 2+14.f, s_Content->s_Window->getSize().y / 2 + 50.f);
	menu[2].setCharacterSize(20);

	menu[0].setOutlineColor(sf::Color::Black);
	menu[1].setOutlineColor(sf::Color::Black);
	menu[2].setOutlineColor(sf::Color::Black);

	menu[0].setOutlineThickness(2);
	menu[1].setOutlineThickness(2);
	menu[2].setOutlineThickness(2);
}

void MainMenu::Input_Processing()
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
					menu[selected_index].setFillColor(sf::Color::White);
					selected_index--;
					menu[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
				}
			case sf::Keyboard::Down:
			{
				if (selected_index + 1 < 3)
				{
					menu[selected_index].setFillColor(sf::Color::White);
					selected_index++;
					menu[selected_index].setFillColor(sf::Color::Yellow);
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				Play_Button_Pressed = false;
				Exit_Button_Pressed = false;
				LeaderBoards_Button_Pressed = false;
				if (selected_index == 0)
				{
					Play_Button_Pressed = true;
				}
				if (selected_index == 1)
				{
					LeaderBoards_Button_Pressed = true;
				}
				if (selected_index == 2)
				{
					Exit_Button_Pressed = true;
				}
				break;
			}
			case sf::Keyboard::Escape:
			{
				s_Content->s_Window->close();
			}
			default:
			{
				break;
			}
			}
		}
		
	}
}

void MainMenu::Update()
{

	if (Play_Button_Pressed)
	{
		s_Content->s_States->PutOnStack(std::make_unique<Play>(s_Content), true);
	}
	else if (Exit_Button_Pressed)
	{
		s_Content->s_Window->close();
	}
}

void MainMenu::Draw()
{
	s_Content->s_Window->clear(sf::Color::Green);
	s_Content->s_Window->draw(Game_Title);
	for (int i = 0; i < 3; i++)
	{
		s_Content->s_Window->draw(menu[i]);
	}
	s_Content->s_Window->display();
}
