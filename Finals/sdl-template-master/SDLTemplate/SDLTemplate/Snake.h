#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
class Snake : public GameObject
{
public:
	void start();
	void update();
	void draw();

private:
	SDL_Texture* head;
	SDL_Texture* body;
	SDL_Texture* tail;
	int x;
	int y;
	int width;
	int height;
};

