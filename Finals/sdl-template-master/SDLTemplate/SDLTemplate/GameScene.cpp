#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor

	pickupCount = 0;
}

GameScene::~GameScene()
{

}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here
}

void GameScene::draw()
{
	Scene::draw();
}

void GameScene::update()
{
	Scene::update();
	if (pickupCount <= 10)
	{
		PickupSpawn();
	}
}

void GameScene::PickupSpawn()
{
	pickup = new Pickup();
	this->addGameObject(pickup);
	int x = rand() % SCREEN_WIDTH;
	int y = rand() % SCREEN_HEIGHT;
	pickup->SetPos(x,y);
	pickupCount++;
}
