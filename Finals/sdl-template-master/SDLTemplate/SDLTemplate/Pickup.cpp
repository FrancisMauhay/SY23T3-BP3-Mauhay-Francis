#include "Pickup.h"

void Pickup::start()
{
	texture = loadTexture("gfx/apple.png");
	width = 0;
	height = 0;
	active = false;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Pickup::update()
{
}

void Pickup::draw()
{
	blit(texture, x, y);
}

void Pickup::onCollide()
{
	delete this;
}

void Pickup::SetPos(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}
