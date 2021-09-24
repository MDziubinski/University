#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>


class PowerUp : public sf::Drawable
{
public:
	sf::Sprite shape;

	PowerUp();
	~PowerUp();
	void Initialize(const sf::Texture& texture, sf::Vector2u pos);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};