#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

using namespace std;

class Player :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    void setSpeed();
    void move();
    void shoot();
    void specialShoot();
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
    vector<Bullet*> bullets;
};

