#include "Enemy.h"

Enemy::Enemy()
	:HPMax(0), HP(0), direction(0), DMG(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(const sf::Texture& texture, sf::Vector2u pos, int temp1, int temp2, int temp3)
{
	shape.setTexture(texture);
	shape.setScale(0.1f, 0.1f);
	shape.setPosition(pos.x - shape.getGlobalBounds().width, rand() % (int)(pos.y - shape.getGlobalBounds().height));
	HPMax = rand() % temp1 + temp2;
	HP = HPMax;
	direction = rand() % 2;
	DMG = temp3;
}

void Enemy::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}