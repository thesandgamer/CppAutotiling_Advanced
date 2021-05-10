#pragma once
#include <iostream>
#include "raylib.h"
#include "RectangleI.h"

class Tile
{
public:
	Tile();
	Tile(int xP, int yP, int sizeP, Texture2D spriteP);
	~Tile();

	int x;
	int y;

	int size;

	Texture2D  sprite;

	void Update();
	void Draw();

	void ChangeSprite(int value);

	int GetX() const;
	int GetY() const;

	RectangleI GetRect();

private:

	Rectangle spriteEmplacement;


};

