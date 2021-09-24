#include "Snake.h"
#include <iostream>

Snake::Snake() : Snake_Body(std::list<sf::Sprite>(5))
{
	Snake_Head = --Snake_Body.end();
	Snake_Tail = Snake_Body.begin();
}

Snake::~Snake()
{
	std::cout << "Snake destructor!" << std::endl;
}


void Snake::Initialize(const sf::Texture& texture)
{
	float x = 16.f;
	for (auto& part : Snake_Body)
	{
		part.setTexture(texture);
		part.setPosition({x,16.f});
		x += 16.f;
	}
}

void Snake::Move(const sf::Vector2f& direction)
{
	Snake_Tail->setPosition(Snake_Head->getPosition() + direction);
	Snake_Head = Snake_Tail;
	++Snake_Tail;

	if (Snake_Tail == Snake_Body.end()) 
	{
		Snake_Tail = Snake_Body.begin();
	}
}

bool Snake::Collision(const sf::Sprite& other) const
{
	return other.getGlobalBounds().intersects(Snake_Head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
	sf::Sprite newPart;
	newPart.setTexture(*(Snake_Body.begin()->getTexture()));
	newPart.setPosition(Snake_Head->getPosition() + direction);
	Snake_Head = Snake_Body.insert(++Snake_Head, newPart);
}

bool Snake::HitItself() const
{
	bool hit = false;

	for (auto part = Snake_Body.begin(); part != Snake_Body.end(); part++)
	{
		if (Snake_Head != part)
		{
			hit = Collision(*part);

			if (hit == true)
			{
				break;
			}
		}

	}
	return hit;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& part : Snake_Body)
	{
		target.draw(part);
	}
}
