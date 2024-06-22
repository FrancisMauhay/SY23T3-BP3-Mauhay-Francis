#pragma once
#include "GameObject.h"
#include "draw.h"
#include "SoundManager.h"

class PowerUp : public GameObject
{
public:
	void start();
	void draw();
	void update();
    void setPos(int posX, int posY);
    void deleteOnCollide();
    int getPositionX();
    int getPositionY();
    int getWidth();
    int getHeight();
private:
    SDL_Texture* texture;
    int x;
    int y;
    int directionY;
    int width;
    int height;
    int speed;
};

