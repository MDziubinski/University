#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>
#include "Bullet.h"

class Spaceship : public sf::Drawable
{
public:
	sf::Sprite shape;

	int HP;
	int HPMax;
	int DMG;

	std::vector<Bullet> bullets;

	Spaceship();
	~Spaceship();
	void Initialize(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};