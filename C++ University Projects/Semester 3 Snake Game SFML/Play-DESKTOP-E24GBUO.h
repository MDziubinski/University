#pragma once
#include<SFML/Graphics/Sprite.hpp>
#include <memory>
#include <array>
#include "State.h"
#include "Game.h"
#include "Snake.h"

class Play : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Sprite grass;
	sf::Sprite apple;
	std::array<sf::Sprite, 4> walls;
	Snake snake;

	sf::Text score;
	int points;
	sf::Vector2f Snake_Direction;
	sf::Time Elapsed_Time;
public:
	Play(std::shared_ptr<Content> &content);
	~Play();

	void Initialize();
	void Input_Processing();
	void Update(); 
	void Draw();

	void Pause(); 
	void Start(); 

};

template <class T>
constexpr const T& clamp(const T& value, const T& min, const T& max)
{
	return value < min ? min : max < value ? max : value;
}