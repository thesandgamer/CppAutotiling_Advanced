#include "Player.h"
#include "raylib.h"
#include <iostream>

int colliding = 0;

Player::Player()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;

}
Rectangle spriteEmplacement;

Player::Player(int xP, int yP, int widthP, int heightP,Texture2D spriteP): x(xP), y(yP), width(widthP),height(heightP), sprite(spriteP)
{
	spriteEmplacement = { 0,0,(float)width,(float)height };
}

Player::~Player()
{

}

int horizontal = 0;
int vertical = 0;

void Player::Update()
{
	colliding = 0;
	MoveSprite();

}

int framesCounter = 0;
int framesSpeed = 8;
int currentFrame = 0;

void Player::MoveSprite()
{
	//Flip l'image si horizontal et > 0
	if (horizontal != 0 || vertical != 0)
	{
		framesCounter++;

		if (framesCounter >= (60 / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;
			std::cout << currentFrame << std::endl;
			if (currentFrame > 2) currentFrame = 0;

			spriteEmplacement.x = (float)currentFrame * 32;
		}
	}

}

void Player::Movement()
{
	//Horizontal
	if (IsKeyDown(KEY_RIGHT))
	{
		horizontal = 1;
	}
	else if (IsKeyDown(KEY_LEFT) )
	{
		horizontal = -1;
	}
	else
	{
		horizontal = 0;
	}

	//Vertical
	if (IsKeyDown(KEY_DOWN))
	{
		vertical = 1;
	}
	else if (IsKeyDown(KEY_UP) )
	{
		vertical = -1;
	}
	else
	{
		vertical = 0;
	}


	
}

void Player::Collisions(int colliding)
{
	if (colliding == 0)
	{
		Move(horizontal, vertical);
	}
	else if (colliding & HitBas && !(colliding & HitDroit) && !(colliding & HitGauche) )
	{
		Move(horizontal, 0);
	}	
	else if (colliding & HitHaut && !(colliding & HitDroit) && !(colliding & HitGauche) )
	{
		Move(horizontal, 0);
	}	
	
	else if (colliding & HitGauche && !(colliding & HitHaut) && !(colliding & HitBas) )
	{
		Move(0, vertical);
	}	
	else if (colliding & HitDroit && !(colliding & HitHaut) && !(colliding & HitBas) )
	{
		Move(0, vertical);
	}

}




void Player::Move(int horizontalValue,int verticalValue)
{
	//Chack des collisions
	x += horizontalValue* speed;
	y += verticalValue* speed;

}

Vector2 Player::GetDirection()
{
	Vector2 direction = { horizontal,vertical };
	return direction;

}

void Player::Draw()
{
	Vector2 pos = { x , y };
	DrawTextureRec(sprite, spriteEmplacement, pos, WHITE);
}


RectangleI Player::GetRect()
{
	DrawRectangle(x,y,width,height,PURPLE);
	return RectangleI{ x,y,width,height};
}