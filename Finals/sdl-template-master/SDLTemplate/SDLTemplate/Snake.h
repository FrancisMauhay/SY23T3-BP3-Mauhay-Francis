#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include <vector>
class Snake : public GameObject
{
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };
	struct SnakeBody 
	{
		int X;
		int Y;
		int prevX;
		int prevY;
	};

	void start();
	void update();
	void draw();

	Direction getDirection();
	void setDirection(Direction newDirection);
	void move();

private:

	SDL_Texture* head;
	SDL_Texture* body;

	Direction direction;

	std::vector<SnakeBody> bodySegments;

	int posX;
	int posY;
	int width;
	int height;
	int speed;
	int points;
	int headDirection;
};

