#pragma once
#include "raylib.h"

class Projectile
{
public:

	Projectile();
	Projectile(float xP, float yP, Vector2 sizeP, Vector2 directionP, float spdP);
	~Projectile();

	void Uptade();
	void Draw();

	void Move();
	Rectangle GetRect();

	float x;
	float y;

	Vector2 direction;
	float spd;
	Vector2 size;

	Rectangle rect;



};

