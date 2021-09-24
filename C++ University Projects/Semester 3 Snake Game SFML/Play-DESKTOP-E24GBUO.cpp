#include "Play.h"
#include "End.h"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>



Play::Play(std::shared_ptr<Content> &content)
	: s_Content(content), Snake_Direction({16.f,0.f}), points(0)
{
	srand(time(nullptr));
}
Play::~Play()
{
	std::cout << "Gameplay destructor!" << std::endl;
	s_Content = nullptr;
}

void Play::Initialize()
{
	s_Content->s_Assets->Add_Texture("Assets/Textures/grass.png", GRASS, true);
	s_Content->s_Assets->Add_Texture("Assets/Textures/wall.png", WALL, true);
	s_Content->s_Assets->Add_Texture("Assets/Textures/apple.png", APPLE);
	s_Content->s_Assets->Add_Texture("Assets/Textures/snake.png", SNAKE);

	grass.setTexture(s_Content->s_Assets->Get_Texture(GRASS));
	grass.setTextureRect(s_Content->s_Window->getViewport(s_Content->s_Window->getDefaultView()));

	apple.setTexture(s_Content->s_Assets->Get_Texture(APPLE));
	apple.setPosition(s_Content->s_Window->getSize().x / 2, s_Content->s_Window->getSize().y / 2);

	score.setFont(s_Content->s_Assets->Get_Font(MAIN_FONT));
	score.setString("Current score: " + std::to_string(points));
	score.setCharacterSize(19);
	score.setFillColor(sf::Color::Black);

	for (auto& wall : walls)
	{
		wall.setTexture(s_Content->s_Assets->Get_Texture(WALL));
	}

	walls[0].setTextureRect({ 0,0,(int)s_Content->s_Window->getSize().x,16 });
	walls[1].setTextureRect({ 0,0,(int)s_Content->s_Window->getSize().x,16 });
	walls[1].setPosition(0, s_Content->s_Window->getSize().y - 16);

	walls[2].setTextureRect({ 0,0,16,(int)s_Content->s_Window->getSize().y });
	walls[3].setTextureRect({ 0,0,16,(int)s_Content->s_Window->getSize().y });
	walls[3].setPosition(s_Content->s_Window->getSize().x - 16, 0);

	snake.Initialize(s_Content->s_Assets->Get_Texture(SNAKE));
}
void Play::Input_Processing()
{
	sf::Event event;
	sf::Vector2f new_direction = Snake_Direction;
	while (s_Content->s_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			s_Content->s_Window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				new_direction = { 0.f,-16.f };
				break;
			}
			case sf::Keyboard::Down:
			{
				new_direction = { 0.f,+16.f };
				break;
			}
			case sf::Keyboard::Right:
			{
				new_direction = { +16.f,0.f };
				break;
			}
			case sf::Keyboard::Left:
			{
				new_direction = { -16.f,0.f };
				break;
			}
			case sf::Keyboard::Escape:
			{
				s_Content->s_States->PutOnStack(std::make_unique<End>(s_Content), true);
			}
			default: break;
			}

			if (std::abs(Snake_Direction.x) != std::abs(new_direction.x) || std::abs(Snake_Direction.y) != std::abs(new_direction.y))
			{
				Snake_Direction = new_direction;
			}
		}
	}
}
void Play::Update()
{
	
	bool Wall_Collision = false;

	for (auto& wall : walls)
	{
		if (snake.Collision(wall))
		{
			s_Content->s_States->PutOnStack(std::make_unique<End>(s_Content), true);
			break;
		}
	}

	if (snake.Collision(apple))
	{

		snake.Grow(Snake_Direction);
		points++;
		score.setString("Current score: " + std::to_string(points));
		

		int x = clamp<int>(rand() % s_Content->s_Window->getSize().x, 16, rand() % s_Content->s_Window->getSize().x -2 * 16);
		int y = clamp<int>(rand() % s_Content->s_Window->getSize().y, 16, rand() % s_Content->s_Window->getSize().y - 2 * 16);
		apple.setPosition(x, y);
	}
	if (snake.HitItself())
	{
		s_Content->s_States->PutOnStack(std::make_unique<End>(s_Content), true);
	}
	else
	{
		snake.Move(Snake_Direction);
	}
}
void Play::Draw()
{
	s_Content->s_Window->clear();
	s_Content->s_Window->draw(grass);

	for (auto& wall : walls)
	{
		s_Content->s_Window->draw(wall);
	}
	s_Content->s_Window->draw(apple);
	s_Content->s_Window->draw(snake);
	s_Content->s_Window->draw(score);
	s_Content->s_Window->display();
}

void Play::Pause() {}
void Play::Start() {}