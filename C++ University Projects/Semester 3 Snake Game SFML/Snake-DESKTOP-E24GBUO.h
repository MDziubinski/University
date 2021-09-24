#pragma once
#include<list>
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/RenderTarget.hpp>
#include<SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
	std::list<sf::Sprite> Snake_Body;
	std::list<sf::Sprite>::iterator Snake_Head;
	std::list<sf::Sprite>::iterator Snake_Tail;


public:
	Snake();
	/*Snake(Snake&& other) : Snake_Body(other.Snake_Body)
	{
		other.Snake_Body = nullptr;

	};
	*/
	~Snake();

	
	void Initialize(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	bool Collision(const sf::Sprite& other) const;
	void Grow(const sf::Vector2f& direction);
	bool HitItself() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

