#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "util.h"
#include "Player.h"
#include <vector>

enum class fireState
{
    fireState_1,
    fireState_2
};

class Boss : public GameObject
{
public:
	void start();
	void update();
	void draw();
    void deductHP();
    void setPos(int posX, int posY);
    void rollState();
    void death();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
    int getHP();
private:
    SDL_Texture* texture;
    Mix_Chunk* fire;
    Player* playerTarget;
    fireState currentState;
    int directionX;
    int directionY;
    float x;
    float y;
    float directionChangeTime;
    float stateChangeTime;
    float currentDirectionChangeTime;
    float currentStateChangeTime;
    float reloadTime;
    float currentReloadTime;
    int width;
    int height;
    int speed;
    int roll;
    int hp;
    vector<Bullet*> bullets;
};

