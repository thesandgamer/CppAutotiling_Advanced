#include "Tile.h"
#include <raylib.h>


Tile::Tile()
{
	x = 0;
	y = 0;
	size = 0;

}

Tile::Tile(int xP, int yP, int sizeP, Texture2D spriteP) : x(xP), y(yP),size(sizeP), sprite(spriteP)
{
}

Tile::~Tile()
{

}


void Tile::ChangeSprite(int value)
{
	
	int v = value;
#pragma region Si faire avec plusieurs colones
	/*
	if (value < 10)
	{
		spriteEmplacement = {v*size,0,size,size};
	}
	else if (value < 20)
	{
		spriteEmplacement = {v*size,1,size,size};
	}
	else if (value < 30)
	{
		spriteEmplacement = {v*size,2,size,size};
	}
	else if (value < 40)
	{
		spriteEmplacement = {v*size,3,size,size};
	}
	else if (value < 50)
	{
		spriteEmplacement = {v*size,4,size,size};
	}
	*/
#pragma endregion

	spriteEmplacement = {(float)v*size,0,(float)size,(float)size}; //Forme un carré de size*size(donc de la taille de la tile), à la position v*size

}


void Tile::Draw()
{
	Vector2 pos = {x * size, y * size };
	DrawTextureRec(sprite, spriteEmplacement, pos,WHITE); //Dessine un carré de taille spriteEmplacement du sprite à la position pos
	
}


RectangleI Tile::GetRect()
{
	DrawRectangle(x*size, y*size, size, size, WHITE);
	return RectangleI{x*size ,y*size,size,size };
}


