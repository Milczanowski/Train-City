#pragma once
#include "Vector2.h"
#include <SDL.h>
class Mouse
{
public:
	Mouse(void);
	~Mouse(void);
	static const Vector2 getMousePosition();
	static const bool checkCollision(const Vector2 center,const float radius);
	static const bool checkCollision(const Vector2 start,const Vector2 size);
};

inline const Vector2 Mouse::getMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Vector2((float)x, (float)y);
}
inline const bool Mouse::checkCollision(const Vector2 center,const float radius)
{
	return (radius >= center.distance(getMousePosition()));
}
inline const bool Mouse::checkCollision(const Vector2 start,const Vector2 size)
{
	Vector2 MousePosition = getMousePosition();
	return (MousePosition >= start) && (MousePosition <= (start + size));
}

