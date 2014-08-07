#include "StdAfx.h"
#include "Mouse.h"
#include <SDL.h>


Mouse::Mouse(void)
{
}

Mouse::~Mouse(void)
{
}

Vector2 Mouse::getMousePosition()
{
	int x,y;
	SDL_GetMouseState(&x,&y);
	return Vector2(x,y);
}
bool Mouse::checkCollision(Vector2 center, float radius)
{
	return (radius>=center.distance(getMousePosition()));
}
bool Mouse::checkCollision(Vector2 start, Vector2 size)
{
	Vector2 MousePosition = getMousePosition();
	return (MousePosition>=start) && (MousePosition<=(start+size));
}