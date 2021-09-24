#include "Asteroid.h"

Asteroid::Asteroid()
{
}
Asteroid::~Asteroid()
{
}

void Asteroid::Initialize(const sf::Texture& texture, sf::Vector2u pos)
{
	shape.setTexture(texture);
	shape.setScale(0.5f, 0.5f);
	shape.setPosition(pos.x - shape.getGlobalBounds().width, rand()% (int)(pos.y - shape.getGlobalBounds().height));
}

void Asteroid::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}