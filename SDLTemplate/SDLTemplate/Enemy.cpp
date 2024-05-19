#include "Enemy.h"
#include "Scene.h"
#include <algorithm>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	texture = loadTexture("gfx/enemy.png");
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	currentReloadTime = 0;
	reloadTime = 60;
	directionChangeTime = (rand() % 300) + 180;
	currentDirectionChangeTime = 0;
	
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	fire = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}
	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}
	if (currentReloadTime == 0)
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(fire);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		currentReloadTime = reloadTime;
	}

	auto it = std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet)
		{
			if (bullet->getPositionX() < 0)
			{
				delete bullet;
				return true;
			}
			return false;
		});

	bullets.erase(it, bullets.end());
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player;
}

void Enemy::setPos(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

float Enemy::getPosX()
{
	return x;
}

float Enemy::getPosY()
{
	return y;
}
