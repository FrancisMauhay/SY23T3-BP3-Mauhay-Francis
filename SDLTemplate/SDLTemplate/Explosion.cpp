#include "Explosion.h"

Explosion::Explosion(int x, int y, float timer) : x(x), y(y), timer(timer)
{
}

void Explosion::start()
{
	texture = loadTexture("gfx/explosion.png");
	timer = 60;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	explode = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	explode->volume = 6;
}

void Explosion::draw()
{
	SoundManager::playSound(explode);
	blit(texture, x, y);
}

void Explosion::update()
{
	if (timer > 0)
	{
		timer--;
	}
	else
	{
		delete this;
	}
}


