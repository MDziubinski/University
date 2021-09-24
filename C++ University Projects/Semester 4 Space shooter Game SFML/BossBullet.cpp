#include "BossBullet.h"

BossBullet::BossBullet()
{
}
BossBullet::~BossBullet()
{
}

void BossBullet::Initialize(const sf::Texture& texture, sf::Vector2f pos)
{
	shape.setTexture(texture);
	shape.setScale(0.1f, 0.1f);
	shape.setPosition(pos);
}

void BossBullet::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void BossBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}