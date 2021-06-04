#pragma once
#include "raylib.h"

class PlayerEnd
{
public:
	PlayerEnd();
	PlayerEnd(int xP, int yP, int widthP, int heightP, Texture2D spriteP);
	~PlayerEnd();

	int x;
	int y;

	int width;
	int height;

	void Update();
	void Draw();

	Texture2D  sprite;

};

