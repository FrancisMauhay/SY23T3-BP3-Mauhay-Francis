#include "Background.h"

void Background::start()
{
	bgTexture = loadTexture("gfx/background.png");
	bgTexture2 = loadTexture("gfx/background.png");
	x = 0;
	y = 0;
	x2 = 600;
	y2 = 0;
	speed = 10;
	scale = 3;
	SDL_QueryTexture(bgTexture, NULL, NULL, &width, &height);
	SDL_QueryTexture(bgTexture2, NULL, NULL, &width, &height);
}

void Background::draw()
{
	blitScale(bgTexture, x, y, &width, &height, scale);
	blitScale(bgTexture2, x2, y2, &width, &height, scale);
}

void Background::update()
{
	x -= speed;
	x2 -= speed;

	if (x + SCREEN_WIDTH < 0)
	{
		x = SCREEN_WIDTH;
	}
	if (x2 + SCREEN_WIDTH < 0)
	{
		x2 = SCREEN_WIDTH;
	}
}

void Background::setPos(int posX, int posY)
{
	this->x2 = posX;
	this->y2 = posY;
}

