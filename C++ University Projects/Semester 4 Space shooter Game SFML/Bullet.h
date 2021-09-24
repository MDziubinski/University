#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>

class Bullet : public sf::Drawable
{
public:
	sf::Sprite shape;
	
	Bullet();
	~Bullet();
	void Initialize(const sf::Texture& texture, sf::Vector2f pos);
	void Move(const sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};