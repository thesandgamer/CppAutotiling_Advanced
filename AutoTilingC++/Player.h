#pragma once

#include "RectangleI.h"
#include "Collisions.h"

class Player
{
public:
	Player();
	Player(int xP, int yP, int widthP, int heightP, Texture2D spriteP);
	~Player();

	int x;
	int y;

	int width;
	int height;
	Texture2D  sprite;

	void Update();
	void Draw();

	void MoveSprite();

	Vector2 GetDirection();

	RectangleI GetRect();

	void Movement();
	void Move(int horizontalValue, int verticalValue);

	void Collisions(int colliding);

private:
	int speed = 2;

};

