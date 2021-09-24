#include "Spaceship.h"
#include <iostream>

Spaceship::Spaceship()
	:HPMax(0), HP(0), DMG(0)
{
}

Spaceship::~Spaceship()
{
}

void Spaceship::Initialize(const sf::Texture& texture)
{
	shape.setTexture(texture);
	shape.setScale(0.5f, 0.5f);
	HPMax = 25;
	HP = HPMax;
	DMG = 50;
}

void Spaceship::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void Spaceship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}