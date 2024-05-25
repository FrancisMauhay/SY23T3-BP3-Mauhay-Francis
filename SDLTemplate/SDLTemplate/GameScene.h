#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
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
	void targetCheck();
private:
	Player* player;
	Background* background;
	Mix_Chunk* bgMusic;
	vector<Enemy*> spawnedEnemies;

	float enemySpawnTime;
	float enemyCurrentSpawnTime;
	bool gameOn;
	int wave;
};

