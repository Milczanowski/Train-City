#pragma once
#include "Vector2.h"
#include <SDL.h>
class Mouse
{
private:
	static Vector2 position;
public:
	Mouse(void);
	~Mouse(void);
	static Vector2 getMousePosition();
	static bool checkCollision(Vector2 center, float radius);
	static bool checkCollision(Vector2 start, Vector2 size);
	
};

