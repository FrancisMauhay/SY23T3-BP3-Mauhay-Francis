#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Pickup.h"
#include "Snake.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	void PickupSpawn();
	void collissionsCheck();
private:
	Snake* snake;
	Pickup* pickup;
	int pickupCount;
};

