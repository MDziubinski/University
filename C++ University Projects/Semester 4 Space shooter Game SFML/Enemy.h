#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include "EnemyBullet.h"

class Enemy : public sf::Drawable
{
public:
	sf::Sprite shape;

	int HPMax;
	int HP;
	int direction;
	int DMG;

	std::vector<EnemyBullet> en_bullets;

	Enemy();
	~Enemy();
	void Initialize(const sf::Texture& texture, sf::Vector2u pos, int temp1, int temp2, int temp3);
	void Move(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};