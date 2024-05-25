#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "util.h"
#include "Player.h"
#include <vector>

using namespace std;

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();
	void start();
	void update();
	void draw();
    void setPlayerTarget(Player* player);
    void setPos(int posX,int posY);
    void deleteMark();
    void targetDeath();
    void resumeShoot();
    bool targetAliveFunc();
    bool deletion();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    Mix_Chunk* fire;
    Player* playerTarget;
    float x;
    float y;
    int width;
    int height;
    int speed;
    float directionX;
    float directionY;
    float reloadTime;
    float currentReloadTime;
    float directionChangeTime;
    float currentDirectionChangeTime;
    bool deleteObj;
    bool targetAlive;
    vector<Bullet*> bullets;

};

