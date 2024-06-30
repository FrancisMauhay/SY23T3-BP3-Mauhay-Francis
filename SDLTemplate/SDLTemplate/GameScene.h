#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "Background.h"
#include "Explosion.h"
#include "PowerUp.h"
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
	void spawnPowerUp();
	void deleteBoss();

private:
	Player* player;
	Background* background;
	Background* background2;
	PowerUp* powerup;
	Boss* boss;
	Mix_Chunk* bgMusic;
	Mix_Chunk* powerUpSound;
	vector<Enemy*> spawnedEnemies;

	float enemySpawnTime;
	float enemyCurrentSpawnTime;
	float powerUpSpawnTime;
	float powerUpCurrentSpawnTime;
	bool gameOn;
	int wave;
	int points;
	int killCount;
	int bossCount;
};

