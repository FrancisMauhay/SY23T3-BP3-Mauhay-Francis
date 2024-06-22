#pragma once
#include "GameObject.h"
#include "draw.h"
#include "SoundManager.h"
class Explosion : public GameObject
{
public:
    Explosion(int x, int y, float timer = 60.0f);
    void start();
    void draw();
    void update();
private:
    SDL_Texture* texture;
    Mix_Chunk* explode;
    int x;
    int y;
    int width;
    int height;
    float timer;
};