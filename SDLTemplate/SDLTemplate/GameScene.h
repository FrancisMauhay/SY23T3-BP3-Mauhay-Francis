#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Explosion.h"
#include "text.h"
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
	Background* background2;
	Mix_Chunk* bgMusic;
	vector<Enemy*> spawnedEnemies;

	float enemySpawnTime;
	float enemyCurrentSpawnTime;
	bool gameOn;
	int wave;
	int points;
};

