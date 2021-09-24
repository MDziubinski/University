#include "Bullet.h"

Bullet::Bullet()
{
}
Bullet::~Bullet()
{
}
void Bullet::Initialize(const sf::Texture& texture, sf::Vector2f pos)
{
	shape.setTexture(texture);
	shape.setScale(0.07f, 0.07f);
	shape.setPosition(pos);
}

void Bullet::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}