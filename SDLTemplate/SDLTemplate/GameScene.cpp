#include "GameScene.h"
#include <algorithm>

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new (Background);
	background2 = new (Background);
	this->addGameObject(background2);
	this->addGameObject(background);
	player = new Player();
	this->addGameObject(player);

	background2->setPos(SCREEN_WIDTH + 1600, 0);
	
	enemyCurrentSpawnTime = 300;
	enemySpawnTime = 300;
	powerUpSpawnTime = 2000;
	powerUpCurrentSpawnTime = 2000;
	points = 0;
	killCount = 0;
	bossCount = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
	SoundManager::loadMusic("music/Mercury.ogg");
	SoundManager::playMusic(1);
	wave = 1;
	initFonts();
	powerUpSound = SoundManager::loadSound("sound/342749__rhodesmas__notification-01.ogg");
	powerUpSound->volume = 20;
}

void GameScene::draw()
{
	Scene::draw();
	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points );

	if (player->isAlive() == false)
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 , 255, 255, 255, TEXT_CENTER, "GAME OVER!");
		points = 0;
		killCount = 0;
		powerUpCurrentSpawnTime = powerUpSpawnTime;
		boss->death();
		boss = nullptr;
		bossCount = 0;
		powerup->deleteOnCollide();
	}
}

void GameScene::update()
{
	Scene::update();

	if (enemyCurrentSpawnTime > 0)
	{
		enemyCurrentSpawnTime--;
	}

	if (bossCount < 1)
	{
		if (enemyCurrentSpawnTime == 0)
		{
			spawn();

			enemyCurrentSpawnTime = enemySpawnTime;
		}
	}

	if (powerUpCurrentSpawnTime > 0)
	{
		powerUpCurrentSpawnTime--;
	}

	if (powerUpCurrentSpawnTime == 0 || killCount >= 10)
	{
		spawnPowerUp();

		powerUpCurrentSpawnTime = powerUpSpawnTime;
		killCount = 0;
	}

	if (wave == 10)
	{
		wave = 3;
	}
	
	collisionCheck();
	enemyDelete();
	targetCheck();
}

void GameScene::spawn()
{
	if (wave != 7)
	{
		for (int i = 0; i < wave; i++)
		{
			Enemy* enemy = new Enemy();
			this->addGameObject(enemy);
			enemy->setPlayerTarget(player);
			enemy->setPos(300 + (rand() % 300), -50);
			spawnedEnemies.push_back(enemy);
		}

		wave++;
	}
	if (wave == 5)
	{
		boss = new Boss();
		this->addGameObject(boss);
		boss->setPos(SCREEN_WIDTH/2, 0);

		bossCount++;
	}
}

void GameScene::collisionCheck()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL)
		{
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
				);

				if (collision == 1)
				{
					float explosionX = player->getPositionX();
					float explosionY = player->getPositionY();

					Explosion* explosion = new Explosion(explosionX, explosionY);
					this->addGameObject(explosion);
					player->death();
					wave = 1;
					
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int enemyCollision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (enemyCollision == 1)
					{
						float explosionX = currentEnemy->getPositionX();
						float explosionY = currentEnemy->getPositionY();

						Explosion* explosion = new Explosion(explosionX, explosionY);
						this->addGameObject(explosion);
						currentEnemy->deleteMark();
						bullet->deleteBulletFunc();
						points++;
						killCount++;
					}
				}

				if (boss != nullptr)
				{
					int bossCollision = checkCollision(
						boss->getPositionX(), boss->getPositionY(), boss->getWidth(), boss->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (bossCollision == 1)
					{
						boss->deductHP();
						cout << "Boss HIT. HP: " << boss->getHP();
						bullet->deleteBulletFunc();

						if (boss->getHP() <= 0)
						{
							float explosionX = boss->getPositionX();
							float explosionY = boss->getPositionY();

							Explosion* explosion = new Explosion(explosionX, explosionY);
							this->addGameObject(explosion);
							boss->death();
							boss = nullptr;
							wave++;
							bossCount = 0;
							points += 50;
							killCount = 10;

						}
					}
				}
			}
		}
		if (powerup != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				powerup->getPositionX(), powerup->getPositionY(), powerup->getWidth(), powerup->getHeight()
			);

			if (collision == 1)
			{
				powerup->deleteOnCollide();
				player->addPower();
				SoundManager::playSound(powerUpSound);
			}
		}
	}
}

void GameScene::enemyDelete()
{
	auto it = std::remove_if(spawnedEnemies.begin(), spawnedEnemies.end(), [](Enemy* enemy)
		{
			if (enemy->deletion() || enemy->getPositionY() > SCREEN_HEIGHT)
			{
				delete enemy;
				return true;
			}
			return false;
		});

	spawnedEnemies.erase(it, spawnedEnemies.end());
}

void GameScene::targetCheck()
{
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		Enemy* currentEnemy = spawnedEnemies[i];

		if (player->isAlive() != true)
		{
			currentEnemy->targetDeath();
		}
		else if (player->isAlive() == true)
		{
			currentEnemy->resumeShoot();
		}
	}
}

void GameScene::spawnPowerUp()
{
	powerup = new PowerUp();
	this->addGameObject(powerup);
	powerup->setPos((rand() % SCREEN_WIDTH), -50);
}
