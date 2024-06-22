#include "Player.h"
#include "Scene.h"
#include <algorithm>

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

void Player::start()
{
	texture = loadTexture("gfx/player.png");
	x = SCREEN_WIDTH/2;
	y = SCREEN_HEIGHT - 200;
	width = 0;
	height = 0;
	speed = 2;
	power = 1;
	spread = 1;
	currentReloadTime = 0;
	reloadTime = 20;
	currentSpecialReloadTime = 0;
	specialReloadTime = 60;
	currentPlayerRespawnTime = 300;
	playerRespawnTime = 300;
	alive = true;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	fire = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	bulletDelete();

	if (!alive)
	{
		respawn();
		return;
	}
	setSpeed();
	move();

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentSpecialReloadTime > 0)
	{
		currentSpecialReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_SPACE] && currentReloadTime == 0)
	{
		shoot();
	}
	
	if (app.keyboard[SDL_SCANCODE_G] && currentSpecialReloadTime == 0)
	{
		specialShoot();
	}
}

void Player::draw()
{
	if (!alive) return;
	blit(texture, x, y);
}

void Player::setSpeed()
{
	if (app.keyboard[SDL_SCANCODE_LSHIFT] && speed == 2)
	{
		speed = 5;
	}
	else if (app.keyboard[SDL_SCANCODE_BACKSPACE] && speed == 5)
	{
		speed = 2;
	}
}

void Player::move()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}
	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
}


void Player::shoot()
{
	SoundManager::playSound(fire);
	for (int i = 0; i < power; i++)
	{
		float angleOffset = (i - power / 2) * (spread * M_PI / 180);

		if (power > 1)
		{
			float directionX = cos(angleOffset);
			float directionY = sin(angleOffset);
			Bullet* bullet = new Bullet(x + width / 2, y, directionX - 1, directionY - 1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}
		else
		{
			float directionX = 0;
			float directionY = sin(angleOffset);
			Bullet* bullet = new Bullet(x + width / 2, y, directionX, directionY - 1, 10, Side::PLAYER_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);
		}
	}
	currentReloadTime = reloadTime;
}

void Player::specialShoot()
{
	SoundManager::playSound(fire);
	Bullet* specialBullet1 = new Bullet(x, y + 3, 1, 0, 10, Side::PLAYER_SIDE);
	Bullet* specialBullet2 = new Bullet(x, y - 2 + height, 1, 0, 10, Side::PLAYER_SIDE);
	getScene()->addGameObject(specialBullet1);
	getScene()->addGameObject(specialBullet2);
	bullets.push_back(specialBullet1);
	bullets.push_back(specialBullet2);

	currentSpecialReloadTime = specialReloadTime;
}

void Player::bulletDelete()
{
	// had asked chatgpt what is a more optimal way of memory management and it suggested using remove_if
	auto it = std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet)
		{
			if (bullet->delBul() || bullet->getPositionY() < 0)
			{
				delete bullet;
				return true;
			}
			return false;
		});

	bullets.erase(it, bullets.end());
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}

int Player::getWidth()
{
	return width;
}

int Player::getHeight()
{
	return height;
}

bool Player::isAlive()
{
	return alive;
}

void Player::death()
{
	alive = false;
}

void Player::respawn()
{
	if (currentPlayerRespawnTime > 0 && !alive)
	{
		currentPlayerRespawnTime--;
	}
	if (currentPlayerRespawnTime == 0 && !alive)
	{
		alive = true;
		reset();
		currentPlayerRespawnTime = playerRespawnTime;
	}
}

void Player::reset()
{
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT - 200;
}

void Player::addPower()
{
	power++;
	spread+=5;
}
