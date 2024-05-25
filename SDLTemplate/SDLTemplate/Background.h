#pragma once
#include "GameObject.h"
#include "draw.h"
class Background : public GameObject
{
public:
	void start();
	void draw();
	void update();
private:
	SDL_Texture* bgTexture;
	int x;
	int y;
	int width;
	int height;
	int speed;
};

