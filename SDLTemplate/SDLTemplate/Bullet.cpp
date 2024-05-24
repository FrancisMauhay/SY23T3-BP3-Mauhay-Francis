#include "Bullet.h"

Bullet::Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side)
{ 
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;
}

void Bullet::start()
{
	if (side == Side::PLAYER_SIDE)
	{
		texture = loadTexture("gfx/playerBullet.png");
	}
	else if (side == Side::ENEMY_SIDE)
	{
		texture = loadTexture("gfx/alienBullet.png");
	}
	width = 0;
	height = 0;
	deleteBullet = false;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

void Bullet::deleteBulletFunc()
{
	deleteBullet = true;
}

bool Bullet::delBul()
{
	return deleteBullet;
}

int Bullet::getPositionX()
{
	return x;
}

int Bullet::getPositionY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet::getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}
