#include "GameScene.h"
#include <algorithm>

GameScene::GameScene()
{
	// Register and add game objects on constructor
	background = new (Background);
	this->addGameObject(background);
	player = new Player();
	this->addGameObject(player);
	
	enemyCurrentSpawnTime = 300;
	enemySpawnTime = 300;
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
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();

	if (enemyCurrentSpawnTime > 0)
	{
		enemyCurrentSpawnTime--;
	}

	if (enemyCurrentSpawnTime == 0)
	{
		spawn();

		enemyCurrentSpawnTime = enemySpawnTime;
		wave++;
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
	for (int i = 0; i < wave; i++)
	{
		Enemy* enemy = new Enemy();
		this->addGameObject(enemy);
		enemy->setPlayerTarget(player);
		enemy->setPos(SCREEN_WIDTH + 150, 300 + (rand() % 300));
		spawnedEnemies.push_back(enemy);
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
					player->death();
					break;
				}
			}
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->getPositionX(), currentEnemy->getPositionY(), currentEnemy->getWidth(), currentEnemy->getHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight()
					);

					if (collision == 1)
					{
						currentEnemy->deleteMark();
						bullet->deleteBulletFunc();
					}
				}
			}
		}
	}
}

void GameScene::enemyDelete()
{
	auto it = std::remove_if(spawnedEnemies.begin(), spawnedEnemies.end(), [](Enemy* enemy)
		{
			if (enemy->deletion() || enemy->getPositionX() < 0)
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
