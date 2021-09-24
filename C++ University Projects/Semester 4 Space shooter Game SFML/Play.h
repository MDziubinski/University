#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "State.h"
#include "Game.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "End.h"
#include "PauseGame.h"
#include "Spaceship.h"
#include "Boss.h"
#include "PowerUp.h"


class Play : public Engine::State
{
	std::shared_ptr<Content> s_Content;
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text enemyHPText;
	sf::Text bossHPText;
	sf::Text damageText;
	Spaceship spaceship;
	Boss boss;
	sf::Vector2f Ship_Direction;
	sf::Vector2f Ship_Position;
	sf::Vector2f Bullet_Direction;
	sf::Vector2f Enemy_Direction;
	sf::Vector2f Enemy_Position;
	sf::Vector2f Enemy_Bullet_Direction;

	sf::Vector2f Boss_Direction;
	sf::Vector2f Boss_Bullet_Direction;
	sf::Vector2f Boss_Position;

	std::vector<Asteroid> asteroids;
	std::vector<Enemy> enemies;
	std::vector<Boss> enemy_boss;
	std::vector<PowerUp> powerups;


	int shootTimer;
	int enShootTimer;
	int asteroidSpawnTimer;
	int enemySpawnTimer;
	int enemySpawnCounter;
	int bossSpawned;
	int bossSpawning;
	int bossSpawnTimer;
	int powerUpSpawned;
	int bossShootTimer;

	//Randomized variables 
	int temp;
	int temp1;
	int temp2;

	int boss_hp_var;
	int boss_dmg;
	int boss_award;

	int enemiesNumber;
	int enemy_hp_var1;
	int enemy_hp_var2;
	int enemy_dmg;

public:
	Play(std::shared_ptr<Content>& content);
	~Play();

	void Initialize(); //Initailizing and setting all fonts and words
	void Input_Processing(); //Processing and handling inputs
	void Update(); //Updating state
	void Draw(); //Drawing on screen menu options and game title

	void Pause(); //Used to pause game
	void Start(); //Used to start game after pause
};