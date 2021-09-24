#include "Boss.h"

Boss::Boss()
	:HPMax(0), HP(0), direction(0), DMG(0)
{
}
Boss::~Boss()
{
}
void Boss::Initialize(const sf::Texture& texture, sf::Vector2u pos, int health, int damage)
{
	shape.setTexture(texture);
	shape.setScale(0.15f, 0.15f);
	shape.setPosition(pos.x - shape.getGlobalBounds().width, rand() % (int)(pos.y - shape.getGlobalBounds().height));
	HPMax = health;
	HP = HPMax;
	direction = rand() % 2;
	DMG = damage;
}
void Boss::Move(const sf::Vector2f& direction)
{
	shape.move(direction);
}

void Boss::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}