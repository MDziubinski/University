#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include "BossBullet.h"

class Boss : public sf::Drawable
{
public:
	sf::Sprite shape;

	int HPMax;
	int HP;
	int direction;
	int DMG;
	
	std::vector<BossBullet> boss_bullets;

	Boss();
	~Boss();
	void Initialize(const sf::Texture& texture, sf::Vector2u pos, int health, int damage);
	void Move(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
