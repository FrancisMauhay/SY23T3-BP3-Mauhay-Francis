#include "Boss.h"
#include "Scene.h"

void Boss::start()
{
	texture = loadTexture("gfx/Boss.png");
	directionX = 1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	hp = 50;
	directionChangeTime = (rand() % 300) + 180;
	currentDirectionChangeTime = 0;
	stateChangeTime = 200;
	currentStateChangeTime = 0;
	currentState = fireState::fireState_1;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	fire = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	fire->volume = 50;
}

void Boss::update()
{
	if (currentStateChangeTime > 0)
	{
		currentStateChangeTime--;
	}
	if (currentStateChangeTime == 0)
	{
		rollState();
		
		currentStateChangeTime = stateChangeTime;
	}

	if (currentState == fireState::fireState_1)
	{
		x += directionX * speed;
		y += directionY * speed;

		if (y > 500)
		{
			directionY = -1;
		}
		if (y < 0)
		{
			directionY = 1;
		}
		if (currentDirectionChangeTime > 0)
		{
			currentDirectionChangeTime--;
		}
		if (currentDirectionChangeTime == 0 || x > SCREEN_WIDTH - width || x < 0)
		{
			directionX = -directionX;
			currentDirectionChangeTime = directionChangeTime;
		}
		if (currentReloadTime > 0)
		{
			currentReloadTime--;
		}
		if (currentReloadTime == 0)
		{
			Bullet* bullet = new Bullet(x+width/2, y - 2 + height / 2, 0, 1, 10, Side::ENEMY_SIDE);
			bullets.push_back(bullet);
			getScene()->addGameObject(bullet);

			currentReloadTime = 30;
		}
	}
	else if (currentState == fireState::fireState_2)
	{
		if (currentReloadTime > 0)
		{
			currentReloadTime--;
		}
		if (currentReloadTime == 0)
		{
			const int numBullets = 15; 
			const float angleIncrement = 2 * M_PI / numBullets; 

			for (int i = 0; i < numBullets; i++)
			{
				float angle = i * angleIncrement;
				float directionX = cos(angle);
				float directionY = sin(angle);
				Bullet* bullet = new Bullet(x + width / 2, y + height / 2, directionX, directionY, 10, Side::ENEMY_SIDE);
				bullets.push_back(bullet);
				getScene()->addGameObject(bullet);
			}

			currentReloadTime = 60;
		}

		directionX = (rand() % 15) + 1;
		directionY = (rand() % 15) + 1;
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

void Boss::draw()
{
	blit(texture, x, y);
}

void Boss::deductHP()
{
	--hp;
}

void Boss::setPos(int posX, int posY)
{
	this->x = posX;
	this->y = posY;
}

void Boss::rollState()
{
	roll = (rand() % 2) + 1;

	if (roll == 1)
	{
		currentState = fireState::fireState_1;
	}
	else if (roll == 2)
	{
		currentState = fireState::fireState_2;
	}
}

void Boss::death()
{
	delete this;
}

int Boss::getPositionX()
{
	return x;
}

int Boss::getPositionY()
{
	return y;
}

int Boss::getWidth()
{
	return width;
}

int Boss::getHeight()
{
	return height;
}

int Boss::getHP()
{
	return hp;
}
