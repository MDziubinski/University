#include "PowerUp.h"

PowerUp::PowerUp()
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::Initialize(const sf::Texture& texture, sf::Vector2u pos)
{
	shape.setTexture(texture);
	shape.setScale(0.1f, 0.1f);
	shape.setPosition(rand() % (pos.x - 200) + 200 , rand() % (pos.y - 200) + 200);
}

void PowerUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}