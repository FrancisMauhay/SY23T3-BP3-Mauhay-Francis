#include "Background.h"

void Background::start()
{
	bgTexture = loadTexture("gfx/background.png");
	bgTexture2 = loadTexture("gfx/background.png");
	x = 0;
	y = 0;
	x2 = 0;
	y2 = -SCREEN_HEIGHT;
	speed = 10;
	scale = 5;
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
	y += speed;
	y2 += speed;

	if (y + SCREEN_HEIGHT > SCREEN_HEIGHT)
	{
		y = -SCREEN_HEIGHT;
	}
	if (y2 + SCREEN_HEIGHT > SCREEN_HEIGHT)
	{
		y2 = -SCREEN_HEIGHT;
	}
}

void Background::setPos(int posX, int posY)
{
	this->x2 = posX;
	this->y2 = posY;
}