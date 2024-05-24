#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

using namespace std;

class Player : public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();
    void setSpeed();
    void move();
    void shoot();
    void specialShoot();
    void bulletDelete();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    bool isAlive();
    void death();
    void respawn();
    void reset();
private:
    SDL_Texture* texture;
    Mix_Chunk* fire;
    int x;
    int y;
    int width;
    int height;
    int speed;
    float reloadTime;
    float currentReloadTime;
    float specialReloadTime;
    float currentSpecialReloadTime;
    float playerRespawnTime;
    float currentPlayerRespawnTime;
    bool alive;
    vector<Bullet*> bullets;
};

