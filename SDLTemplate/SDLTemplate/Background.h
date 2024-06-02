#pragma once
#include "GameObject.h"
#include "draw.h"
class Background : public GameObject
{
public:
	void start();
	void draw();
	void update();
	void setPos(int posX,int posY);
private:
	SDL_Texture* bgTexture;
	SDL_Texture* bgTexture2;
	int x;
	int y;
	int x2;
	int y2;
	int width;
	int height;
	int speed;
	int scale;
};

