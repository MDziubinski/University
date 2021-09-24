#include "Play.h"


Play::Play(std::shared_ptr<Content>& content)
	:s_Content(content), shootTimer(0), asteroidSpawnTimer(0),
	enemySpawnTimer(0), enemySpawnCounter(0), enShootTimer(0),
	bossSpawned(0), bossSpawnTimer(0), bossSpawning(0), powerUpSpawned(0),
	bossShootTimer(0), temp(1000), temp1(1500), temp2(500), enemiesNumber(2),
	enemy_hp_var1(30), enemy_hp_var2(15), enemy_dmg(5),
	boss_hp_var(1000), boss_dmg(50), boss_award(250)
{
}
Play::~Play()
{
}

void Play::Initialize()
{
	srand(time(NULL));
	s_Content->s_File->score = 0;

	//Adding textures and fonts
	s_Content->s_Assets->Add_Texture("Assets/Textures/nightraider.png", PLAYER);
	s_Content->s_Assets->Add_Texture("Assets/Textures/missileTex01.png", BULLET);
	s_Content->s_Assets->Add_Texture("Assets/Textures/asteroid.png", ASTEROID);
	s_Content->s_Assets->Add_Texture("Assets/Textures/enemy.png", ENEMY);
	s_Content->s_Assets->Add_Texture("Assets/Textures/missileTex02.png", EN_BULLET);
	s_Content->s_Assets->Add_Texture("Assets/Textures/boss.png", BOSS);
	s_Content->s_Assets->Add_Texture("Assets/Textures/powerup.png", POWERUP);
	s_Content->s_Assets->Add_Texture("Assets/Textures/boss_bullet.png", BOSS_BULLET);
	s_Content->s_Assets->Add_Font("Assets/Font/Dosis-Light.ttf", SECONDARY_FONT);

	//Score Text
	scoreText.setFont(s_Content->s_Assets->Get_Font(SECONDARY_FONT));
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10.f, 10.f);
	
	//Health Text
	healthText.setFont(s_Content->s_Assets->Get_Font(SECONDARY_FONT));
	healthText.setCharacterSize(20);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(150.f, 10.f);

	//Damage Text
	damageText.setFont(s_Content->s_Assets->Get_Font(SECONDARY_FONT));
	damageText.setCharacterSize(20);
	damageText.setFillColor(sf::Color::White);
	damageText.setPosition(250.f, 10.f);

	//Enemy HP Text
	enemyHPText.setFont(s_Content->s_Assets->Get_Font(SECONDARY_FONT));
	enemyHPText.setCharacterSize(12);
	enemyHPText.setFillColor(sf::Color::White);

	//Boss HP Text
	bossHPText.setFont(s_Content->s_Assets->Get_Font(SECONDARY_FONT));
	bossHPText.setCharacterSize(12);
	bossHPText.setFillColor(sf::Color::White);

	//Spaceship
	spaceship.Initialize(s_Content->s_Assets->Get_Texture(PLAYER));
	spaceship.shape.setPosition(sf::Vector2f(spaceship.shape.getPosition().x, s_Content->s_Window->getSize().y / 2-(spaceship.shape.getTexture()->getSize().y * spaceship.shape.getScale().y/2)));
}

void Play::Input_Processing()
{
	sf::Event event;
	while (s_Content->s_Window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			s_Content->s_Window->close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			s_Content->s_States->PutOnStack(std::make_unique<PauseGame>(s_Content), false);
		}
	}
}

void Play::Update()
{
	//Player
	if (spaceship.HP > 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			Ship_Direction = { 0.f, -10.f };
			spaceship.Move(Ship_Direction);
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			Ship_Direction = { 0.f, 10.f };
			spaceship.Move(Ship_Direction);
		}
			
		//Top move restriction
		if (spaceship.shape.getPosition().y <= 0)
			spaceship.shape.setPosition(spaceship.shape.getPosition().x, 0.f);
		//Bottom move restriction
		if (spaceship.shape.getPosition().y >= s_Content->s_Window->getSize().y - spaceship.shape.getGlobalBounds().height)
			spaceship.shape.setPosition(spaceship.shape.getPosition().x, s_Content->s_Window->getSize().y - spaceship.shape.getGlobalBounds().height);

		if (shootTimer < 15)
			shootTimer++;

		//Bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootTimer >= 15) //Shooting
		{
			Bullet bullet;
			Ship_Position = { spaceship.shape.getPosition().x + (spaceship.shape.getTexture()->getSize().x * spaceship.shape.getScale().x),  spaceship.shape.getPosition().y + (spaceship.shape.getTexture()->getSize().y * spaceship.shape.getScale().y / 2) };
			bullet.Initialize(s_Content->s_Assets->Get_Texture(BULLET), Ship_Position);
			spaceship.bullets.push_back(bullet);
			shootTimer = 0; //reset timer
		}
		Bullet_Direction = { 20.f, 0.f };

		//Asteroids collision with spaceship bullets
		for (size_t i = 0; i < spaceship.bullets.size(); i++)
		{
			spaceship.bullets[i].Move(Bullet_Direction);

			if (spaceship.bullets[i].shape.getPosition().x > s_Content->s_Window->getSize().x)
			{
				spaceship.bullets.erase(spaceship.bullets.begin() + i);
				break;
			}

			for (size_t k = 0; k < asteroids.size(); k++)
			{
				if (spaceship.bullets[i].shape.getGlobalBounds().intersects(asteroids[k].shape.getGlobalBounds()))
				{
					asteroids.erase(asteroids.begin() + k);
					s_Content->s_File->score++;
					spaceship.bullets.erase(spaceship.bullets.begin() + i);
					break;
				}
			}
		}

		//Enemy spaceships collision with player bullets
		for (size_t i = 0; i < spaceship.bullets.size(); i++)
		{
			spaceship.bullets[i].Move(Bullet_Direction);

			if (spaceship.bullets[i].shape.getPosition().x > s_Content->s_Window->getSize().x)
			{
				spaceship.bullets.erase(spaceship.bullets.begin() + i);
				break;
			}

			for (size_t j = 0; j < enemies.size(); j++)
			{
				if (spaceship.bullets[i].shape.getGlobalBounds().intersects(enemies[j].shape.getGlobalBounds()))
				{
					enemies[j].HP -= spaceship.DMG; //ENEMY TAKE DAMAGE
					if (enemies[j].HP <= 1)
					{
						s_Content->s_File->score += enemies[j].HPMax;
						enemies.erase(enemies.begin() + j);
					}

					spaceship.bullets.erase(spaceship.bullets.begin() + i);
					break;
				}
			}
		}

		//Power Up collision with player bullets
		for (size_t i = 0; i < spaceship.bullets.size(); i++)
		{
			spaceship.bullets[i].Move(Bullet_Direction);

			if (spaceship.bullets[i].shape.getPosition().x > s_Content->s_Window->getSize().x)
			{
				spaceship.bullets.erase(spaceship.bullets.begin() + i);
				break;
			}

			for (size_t j = 0; j < powerups.size(); j++)
			{
				if (spaceship.bullets[i].shape.getGlobalBounds().intersects(powerups[j].shape.getGlobalBounds()))
				{
					spaceship.HPMax += 20;
					spaceship.HP = spaceship.HPMax;
					spaceship.DMG += 20;
					powerUpSpawned = 0;
					powerups.erase(powerups.begin() + j);

					spaceship.bullets.erase(spaceship.bullets.begin() + i);
					break;
				}
			}
		}

		//Boss Collision with player bullets
		if (bossSpawned == 1) 
		{
			for (size_t i = 0; i < spaceship.bullets.size(); i++)
			{
				spaceship.bullets[i].Move(Bullet_Direction);

				if (spaceship.bullets[i].shape.getPosition().x > s_Content->s_Window->getSize().x)
				{
					spaceship.bullets.erase(spaceship.bullets.begin() + i);
					break;
				}
				for (size_t j = 0; j < enemy_boss.size(); j++)
				{
					if (spaceship.bullets[i].shape.getGlobalBounds().intersects(enemy_boss[j].shape.getGlobalBounds()))
					{
						enemy_boss[j].HP -= spaceship.DMG; //ENEMY BOSS TAKES DAMAGE
						if (enemy_boss[j].HP <= 1)
						{
							s_Content->s_File->score += 250;
							spaceship.HPMax += 10;
							spaceship.HP = spaceship.HPMax;
							spaceship.DMG += 10;
							bossSpawned = 0;
							bossSpawning = 0;
							boss_hp_var += 500;
							boss_dmg += 25;
							boss_award += 100;
							enemy_boss.erase(enemy_boss.begin() + j);
						}

						spaceship.bullets.erase(spaceship.bullets.begin() + i);
						break;
					}
				}
			}
		}
		
		//Enemy bullets spawn as well as collision with player spaceship
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (enShootTimer < 151)
				enShootTimer++;
			if (rand() % 4 != 0 && enShootTimer >= 151) //Shooting
			{
				EnemyBullet enemy_bullet;
				Enemy_Position = { enemies[i].shape.getPosition().x,  enemies[i].shape.getPosition().y + (enemies[i].shape.getTexture()->getSize().y * enemies[i].shape.getScale().y / 2) };
				enemy_bullet.Initialize(s_Content->s_Assets->Get_Texture(EN_BULLET), Enemy_Position);
				enemies[i].en_bullets.push_back(enemy_bullet);
				enShootTimer = 0;
			}
			Enemy_Bullet_Direction = {-20.f , 0.f};
			for (size_t k = 0; k < enemies[i].en_bullets.size(); k++)
			{
				enemies[i].en_bullets[k].Move(Enemy_Bullet_Direction);
				if (enemies[i].en_bullets[k].shape.getPosition().x < 0)
				{
					enemies[i].en_bullets.erase(enemies[i].en_bullets.begin() + k);
					break;
				}
				//SpaceShip collision with enemy bullets
				if (enemies[i].en_bullets[k].shape.getGlobalBounds().intersects(spaceship.shape.getGlobalBounds()))
				{
					spaceship.HP -= enemies[i].DMG;
					enemies[i].en_bullets.erase(enemies[i].en_bullets.begin() + k);
					break;
				}
			}
		}

		//Boss bullets spawn as well as collision with player spaceship
		if (bossSpawned == 1)
		{
			for (size_t i = 0; i < enemy_boss.size(); i++)
			{
				//enShootTimer = 0;
				if (bossShootTimer < 50)
					bossShootTimer++;
				if (rand() % 5 != 1 && bossShootTimer >= 50) //Shooting
				{
					BossBullet boss_bullet;
					Boss_Position = { enemy_boss[i].shape.getPosition().x,  enemy_boss[i].shape.getPosition().y + (enemy_boss[i].shape.getTexture()->getSize().y * enemy_boss[i].shape.getScale().y / 2) };
					boss_bullet.Initialize(s_Content->s_Assets->Get_Texture(BOSS_BULLET), Boss_Position);
					enemy_boss[i].boss_bullets.push_back(boss_bullet);
					bossShootTimer = 0;
				}
				Boss_Bullet_Direction = {-20.f , 0.f};
				for (size_t k = 0; k < enemy_boss[i].boss_bullets.size(); k++)
				{
					enemy_boss[i].boss_bullets[k].Move(Boss_Bullet_Direction);
					if (enemy_boss[i].boss_bullets[k].shape.getPosition().x < 0)
					{
						enemy_boss[i].boss_bullets.erase(enemy_boss[i].boss_bullets.begin() + k);
						break;
					}
					//SpaceShip collision with boss bullets
					if (enemy_boss[i].boss_bullets[k].shape.getGlobalBounds().intersects(spaceship.shape.getGlobalBounds()))
					{
						spaceship.HP -= enemy_boss[i].DMG;
						enemy_boss[i].boss_bullets.erase(enemy_boss[i].boss_bullets.begin() + k);
						break;
					}
				}
			}
		}
		
		//Asteroids Spawn
		if (asteroidSpawnTimer < 75)
			asteroidSpawnTimer++;

		if (asteroidSpawnTimer >= 75 && bossSpawning == 0)
		{
			Asteroid asteroid;
			asteroid.Initialize(s_Content->s_Assets->Get_Texture(ASTEROID), s_Content->s_Window->getSize());
			asteroids.push_back(asteroid);
			asteroidSpawnTimer = 0; //reset timer
		}

		//Asteroid collision with players spaceship
		if (asteroids.size() > 0)
		{
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				asteroids[i].shape.move(-(float(rand() % 7 + 1)), 0.f);

				if (asteroids[i].shape.getPosition().x <= 0 - asteroids[i].shape.getGlobalBounds().width)
				{
					asteroids.erase(asteroids.begin() + i);
					break;
				}

				if (asteroids[i].shape.getGlobalBounds().intersects(spaceship.shape.getGlobalBounds()))
				{
					asteroids.erase(asteroids.begin() + i);

					spaceship.HP--; // PLAYER TAKE DAMAGE
					break;
				}
			}
		}
		
		//Enemy spawn and movement
		if (enemySpawnTimer < 75)
			enemySpawnTimer++;

		if (enemySpawnTimer >= 75 && enemies.size() <= enemiesNumber && bossSpawning == 0)
		{
			Enemy enemy;
			enemy.Initialize(s_Content->s_Assets->Get_Texture(ENEMY), s_Content->s_Window->getSize(), enemy_hp_var1, enemy_hp_var2, enemy_dmg);
			enemies.push_back(enemy);
			enemySpawnTimer = 0; //reset timer

		}
		if (enemies.size() > 0)
		{
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].shape.getPosition().y + enemies[i].shape.getTexture()->getSize().y * enemies[i].shape.getScale().y < s_Content->s_Window->getSize().y && enemies[i].direction == 0)
				{
					Enemy_Direction = { 0.f, float(rand() % 7 + 1) };
					enemies[i].Move(Enemy_Direction);
					if (enemies[i].shape.getPosition().y + enemies[i].shape.getTexture()->getSize().y * enemies[i].shape.getScale().y >= s_Content->s_Window->getSize().y)
					{
						enemies[i].direction = 1;
					}
				}
				if (enemies[i].shape.getPosition().y > 0 && enemies[i].direction == 1)
				{
					Enemy_Direction = { 0.f, -(float(rand() % 7 + 1)) };
					enemies[i].Move(Enemy_Direction);
					if (enemies[i].shape.getPosition().y <= 0)
					{
						enemies[i].direction = 0;
					}
				}
			}
		}
		

		//Boss spawn and movement
		if (s_Content->s_File->score >= temp)
			bossSpawning = 1;
		if (enemies.size() == 0 && asteroids.size() == 0 && bossSpawning == 1 && bossSpawned == 0)
		{
			boss.Initialize(s_Content->s_Assets->Get_Texture(BOSS), s_Content->s_Window->getSize(), boss_hp_var, boss_dmg);
			bossSpawned = 1;
			enemy_boss.push_back(boss);
		}
		if(bossSpawned == 1)
		{	
			for (size_t i = 0; i < enemy_boss.size(); i++)
			{
				if (enemy_boss[i].shape.getPosition().y + enemy_boss[i].shape.getTexture()->getSize().y * enemy_boss[i].shape.getScale().y < s_Content->s_Window->getSize().y && enemy_boss[i].direction == 0)
				{

					Boss_Direction = { 0.f, float(rand() % 7 + 1) };
					enemy_boss[i].Move(Boss_Direction);
					if (enemy_boss[i].shape.getPosition().y + enemy_boss[i].shape.getTexture()->getSize().y * enemy_boss[i].shape.getScale().y >= s_Content->s_Window->getSize().y)
					{
						enemy_boss[i].direction = 1;
					}
				}
				if (enemy_boss[i].shape.getPosition().y > 0 && enemy_boss[i].direction == 1)
				{
					Boss_Direction = { 0.f, -(float(rand() % 7 + 1)) };
					enemy_boss[i].Move(Boss_Direction);
					if (enemy_boss[i].shape.getPosition().y <= 0)
					{
						enemy_boss[i].direction = 0;
					}
				}
			}
		}
		//Power Up spawn
		if (rand() % 50 == 1 && powerUpSpawned == 0 && s_Content->s_File->score >= temp2 && bossSpawned == 0)
		{	
			PowerUp powerup;
			powerup.Initialize(s_Content->s_Assets->Get_Texture(POWERUP), s_Content->s_Window->getSize());
			
			powerups.push_back(powerup);
			powerUpSpawned = 1;
		}

		//Variables for randomization
		if (s_Content->s_File->score >= temp)
		{
			temp *= 2.5;
		}
		if (s_Content->s_File->score >= temp1)
		{
			temp1 += 1500;
			enemiesNumber++;
			enemy_dmg += 5;
		}
		if (s_Content->s_File->score >= temp2 + 15)
		{
			temp2 += 500;
			enemy_hp_var1 += 2;
			enemy_hp_var2 += 2;
		}

		scoreText.setString("Score: " + std::to_string(s_Content->s_File->score));
		healthText.setString("Health: " + std::to_string(spaceship.HP));
		damageText.setString("Damage: " + std::to_string(spaceship.DMG));
}
	else
		s_Content->s_States->PutOnStack(std::make_unique<End>(s_Content), true);
}

void Play::Draw()
{
	s_Content->s_Window->clear(sf::Color::Black);
	s_Content->s_Window->draw(scoreText);
	s_Content->s_Window->draw(healthText);
	s_Content->s_Window->draw(damageText);
	s_Content->s_Window->draw(spaceship);

	for (size_t i = 0; i < spaceship.bullets.size(); i++)
	{
		s_Content->s_Window->draw(spaceship.bullets[i].shape);
	}

	for (size_t i = 0; i < asteroids.size(); i++)
	{
		s_Content->s_Window->draw(asteroids[i].shape);
	}

	for (size_t i = 0; i < powerups.size(); i++)
	{
		s_Content->s_Window->draw(powerups[i].shape);
	}

	for (size_t i = 0; i < enemies.size(); i++)
	{	
		enemyHPText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
		enemyHPText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - enemyHPText.getGlobalBounds().height);
		s_Content->s_Window->draw(enemyHPText);
		s_Content->s_Window->draw(enemies[i].shape);

		for (size_t k = 0; k < enemies[i].en_bullets.size(); k++)
		{
			s_Content->s_Window->draw(enemies[i].en_bullets[k].shape);
		}
	}

	if (bossSpawned == 1)
	{
		for (size_t i = 0; i < enemy_boss.size(); i++)
		{
			bossHPText.setString(std::to_string(enemy_boss[i].HP) + "/" + std::to_string(enemy_boss[i].HPMax));
			bossHPText.setPosition(enemy_boss[i].shape.getPosition().x, enemy_boss[i].shape.getPosition().y - bossHPText.getGlobalBounds().height);
			s_Content->s_Window->draw(bossHPText);
			s_Content->s_Window->draw(enemy_boss[i]);

			for (size_t k = 0; k < enemy_boss[i].boss_bullets.size(); k++)
			{
				s_Content->s_Window->draw(enemy_boss[i].boss_bullets[k].shape);
			}
		}
	}

	s_Content->s_Window->display();
}

void Play::Pause() {}
void Play::Start() {}