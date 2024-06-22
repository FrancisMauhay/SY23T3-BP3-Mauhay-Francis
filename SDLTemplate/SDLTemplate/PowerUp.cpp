#include "PowerUp.h"

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::update()
{
	y += directionY * speed;
}

void PowerUp::setPos(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

void PowerUp::deleteOnCollide()
{
	delete this;
}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}
