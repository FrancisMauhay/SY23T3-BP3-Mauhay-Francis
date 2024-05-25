#include "Background.h"

void Background::start()
{
	bgTexture = loadTexture("gfx/background.png");
	x = 600;
	y = 600;
	speed = 10;
	SDL_QueryTexture(bgTexture, NULL, NULL, &width, &height);
}

void Background::draw()
{
	blit(bgTexture, x, y);
}

void Background::update()
{
	x -= speed;
}
