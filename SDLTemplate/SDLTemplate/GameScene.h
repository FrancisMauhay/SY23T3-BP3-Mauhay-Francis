#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

using namespace std;

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
	void spawn();
	void collisionCheck();
	void enemyDelete();
private:
	Player* player;
	vector<Enemy*> spawnedEnemies;

	float enemySpawnTime;
	float enemyCurrentSpawnTime;
	int wave;
};

