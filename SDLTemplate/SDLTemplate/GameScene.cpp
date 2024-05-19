#include "GameScene.h"
#include <algorithm>

GameScene::GameScene()
{
	// Register and add game objects on constructor
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
		wave == 3;
	}
	
	auto it = std::remove_if(spawnedEnemies.begin(), spawnedEnemies.end(), [](Enemy* enemy)
		{
			if (enemy->getPosX() < 0)
			{
				delete enemy;
				return true;
			}
			return false;
		});

	spawnedEnemies.erase(it, spawnedEnemies.end());
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
