#include "Leaderboards.h"

Leaderboards::Leaderboards(std::shared_ptr<Content>& content)
	:s_Content(content), LeaderBoards_Exit_Button_Pressed(false), var(0), dist(30.f)
{
}
Leaderboards::~Leaderboards()
{
}

void Leaderboards::Initialize()
{
	for (auto const& element : s_Content->s_File->leaderboards)
	{
		if (var < 10)
		{
			players.push_back(element);
			var++;
		}
	}

	for (size_t i = 0; i < players.size(); i++)
	{	
		var_text.setString(players[i].second + ' ' + std::to_string(players[i].first));
		playerTexts.push_back(var_text);
	}

	for (size_t i = 0; i < playerTexts.size(); i++)
	{
		playerTexts[i].setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
		playerTexts[i].setOutlineThickness(2);
		playerTexts[i].setCharacterSize(25);
		playerTexts[i].setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * playerTexts[i].getLocalBounds().width, s_Content->s_Window->getSize().y / 2 + dist);
		playerTexts[i].setFillColor(sf::Color::White);
		playerTexts[i].setOutlineColor(sf::Color::Black);
		dist += 30.f;
	}

	leaderboard_text.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	leaderboard_text.setString("Leaderboards");
	leaderboard_text.setOutlineThickness(2);
	leaderboard_text.setCharacterSize(25);
	leaderboard_text.setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 *leaderboard_text.getLocalBounds().width, s_Content->s_Window->getSize().y / 2 - 200.f);
	leaderboard_text.setFillColor(sf::Color::White);
	leaderboard_text.setOutlineColor(sf::Color::Black);
	
	top_ten.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	top_ten.setString("Top 10 Players");
	top_ten.setOutlineThickness(2);
	top_ten.setCharacterSize(25);
	top_ten.setPosition(s_Content->s_Window->getSize().x / 2 - 0.5 * top_ten.getLocalBounds().width, s_Content->s_Window->getSize().y / 2 - 100.f);
	top_ten.setFillColor(sf::Color::White);
	top_ten.setOutlineColor(sf::Color::Black);
	
	s_Content->s_Assets->Add_Texture("Assets/Textures/spacev2.png", BACKGROUND);
	Background.setTexture(s_Content->s_Assets->Get_Texture(BACKGROUND));
	Background.setPosition(0, 0);
}
void Leaderboards::Input_Processing()
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
				LeaderBoards_Exit_Button_Pressed = true;
			}
		}

	}
}
void Leaderboards::Update()
{
	if (LeaderBoards_Exit_Button_Pressed)
	{
		s_Content->s_States->PutOnStack(std::make_unique<MainMenu>(s_Content), true);
	}
}
void Leaderboards::Draw()
{
	s_Content->s_Window->clear();
	s_Content->s_Window->draw(Background);
	s_Content->s_Window->draw(leaderboard_text);
	s_Content->s_Window->draw(top_ten);
	
	for (size_t i = 0; i < playerTexts.size(); i++)
	{
		s_Content->s_Window->draw(playerTexts[i]);
	}
	s_Content->s_Window->display();
}