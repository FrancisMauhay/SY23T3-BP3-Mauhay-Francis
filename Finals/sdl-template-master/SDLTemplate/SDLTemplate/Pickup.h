#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"

class Pickup :
    public GameObject
{
public:
    void start();
    void update();
    void draw();
    void onCollide();
    void SetPos(int posX, int posY);

private:
    SDL_Texture* texture;
    Mix_Chunk* sound;
    int x;
    int y;
    int width;
    int height;
    bool active;
};

