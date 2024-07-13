#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Pickup.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	void PickupSpawn();
private:
	Pickup* pickup;
	int pickupCount;
};

