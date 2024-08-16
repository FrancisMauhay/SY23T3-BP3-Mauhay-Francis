#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	snake = new Snake();
	this->addGameObject(snake);
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
	if (pickupCount == 0)
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

void GameScene::collissionsCheck()
{
	for (int i = 0; i < objects.size(); i++)
	{
		Pickup* pickup = dynamic_cast<Pickup*>(objects[i]);

		if (pickup != NULL)
		{

		}
	}
}
