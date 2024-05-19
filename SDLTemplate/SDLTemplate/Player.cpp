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
	x = 100;
	y = 300;
	width = 0;
	height = 0;
	speed = 2;
	currentReloadTime = 0;
	reloadTime = 20;
	currentSpecialReloadTime = 0;
	specialReloadTime = 60;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	fire = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
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

	// had asked chatgpt what is a more optimal way of memory management and it suggested using remove_if
	auto it = std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet) 
		{
		if (bullet->getPositionX() > SCREEN_WIDTH) 
		{
			delete bullet;
			return true;
		}
		return false;
		});

	bullets.erase(it, bullets.end());
}

void Player::draw()
{
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
	Bullet* bullet = new Bullet(x + width ,y - 2 + height/2 ,1,0,10);
	bullets.push_back(bullet);
	getScene()->addGameObject(bullet);

	currentReloadTime = reloadTime;
}

void Player::specialShoot()
{
	SoundManager::playSound(fire);
	Bullet* specialBullet1 = new Bullet(x, y + 3, 1, 0, 10);
	Bullet* specialBullet2 = new Bullet(x, y - 2 + height, 1, 0, 10);
	getScene()->addGameObject(specialBullet1);
	getScene()->addGameObject(specialBullet2);
	bullets.push_back(specialBullet1);
	bullets.push_back(specialBullet2);

	currentSpecialReloadTime = specialReloadTime;
}

int Player::getPositionX()
{
	return x;
}

int Player::getPositionY()
{
	return y;
}
