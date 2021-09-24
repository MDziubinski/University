#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Initialize(const sf::Texture& texture, sf::Vector2f pos)
{
	shape.setTexture(texture);
	shape.setScale(0.07f, 0.07f);
	shape.setPosition(pos);
}

void EnemyBullet::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void EnemyBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}