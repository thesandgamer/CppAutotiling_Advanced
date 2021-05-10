#include "Projectile.h"

Projectile::Projectile()
{
	x = 0;
	y = 0;
	size = { 0,0 };
	spd = 0;
	direction = { 0,0 };
	rect = { 0,0 };

}

Projectile::Projectile(float xP, float yP, Vector2 sizeP,Vector2 directionP, float spdP) : x(xP), y(yP), size(sizeP), direction(directionP),spd(spdP)
{
}

Projectile::~Projectile()
{

}


void Projectile::Move()
{
	x += direction.x * spd;
	y += direction.y * spd;
}

void Projectile::Uptade()
{
	Move();
}

Rectangle Projectile::GetRect()
{
	Rectangle rect = { x-(size.x/2),y-(size.y / 2),size.x,size.y };
	DrawRectangleLines(rect.x, rect.y, rect.width, rect.height, YELLOW);
	return rect;
}


void Projectile::Draw()
{
	DrawCircle(x, y, size.x/2, BLUE);
}