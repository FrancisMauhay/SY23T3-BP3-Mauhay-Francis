#include "Snake.h"

void Snake::start()
{
	head = loadTexture("gfx/head_right.png");
	body = loadTexture("gfx/body_horizontal.png");
	width = 0;
	height = 0;
	speed = 4;
	points = 0;
	direction = Direction::LEFT;

	SnakeBody headArea;
	headArea.X = SCREEN_WIDTH / 2;
	headArea.Y = SCREEN_HEIGHT / 2;

	bodySegments.push_back(headArea);

	SDL_QueryTexture(head, NULL, NULL, &width, &height);
	SDL_QueryTexture(body, NULL, NULL, &width, &height);
}

void Snake::update()
{
	move();
	if (direction == Direction::UP)
	{
		headDirection = 270;
		bodySegments[0].prevY = bodySegments[0].Y;
		bodySegments[0].Y -= speed;
	}
	if (direction == Direction::DOWN)
	{
		headDirection = 90;
		bodySegments[0].prevY = bodySegments[0].Y;

		bodySegments[0].Y += speed;
	}
	if (direction == Direction::LEFT)
	{
		headDirection = 180;
		bodySegments[0].prevX = bodySegments[0].X;
		bodySegments[0].X -= speed;
	}
	if (direction == Direction::RIGHT)
	{
		headDirection = 0;
		bodySegments[0].prevX = bodySegments[0].X;
		bodySegments[0].X += speed;

	}
}

void Snake::draw()
{
	for (int i = 0; i < bodySegments.size(); i++)
	{
		if (i == 0)
		{
			blitRotate(head, bodySegments[i].X, bodySegments[i].Y, headDirection);
		}
		else
		{
			blitRotate(body, bodySegments[i].X, bodySegments[i].Y, headDirection);
		}
	}
}

Snake::Direction Snake::getDirection()
{
	return direction;
}

void Snake::setDirection(Direction newDirection)
{
	this->direction = newDirection;
}

void Snake::move()
{
	if (app.keyboard[SDL_SCANCODE_W] && direction != Direction::DOWN)
	{
		direction = Direction::UP;
	}
	if (app.keyboard[SDL_SCANCODE_A] && direction != Direction::RIGHT)
	{
		direction = Direction::LEFT;
	}
	if (app.keyboard[SDL_SCANCODE_S] && direction != Direction::UP)
	{
		direction = Direction::DOWN;
	}
	if (app.keyboard[SDL_SCANCODE_D] && direction != Direction::LEFT)
	{
		direction = Direction::RIGHT;
	}
}
