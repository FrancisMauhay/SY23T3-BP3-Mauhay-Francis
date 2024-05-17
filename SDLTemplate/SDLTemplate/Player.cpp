#include "Player.h"

void Player::start()
{
	texture = loadTexture("gfx/player.png");
	x = 100;
	y = 300;
	width = 0;
	height = 0;
	speed = 2;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	setSpeed();
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
