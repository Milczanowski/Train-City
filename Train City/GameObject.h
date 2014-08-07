#include "Vector2.h"
#include <SDL.h>
#include <math.h>
#include "GraphicDevice.h"
#include "Mouse.h"
#include <string.h>

using namespace std;

#pragma once
class GameObject
{
protected:
	Vector2 position;
	Vector2 scale;
	static SDL_Event _event;
	float angle;
	SDL_Texture * texture;
	bool _onMouseDown;
public:
	GameObject(void);
	GameObject(const Vector2 position, const Vector2 scale, const float angle,SDL_Texture* texture);
	virtual~GameObject(void);

	virtual void draw();
	virtual void update();
	virtual void onMouseOver();
	virtual void onMouseNotOver();
	virtual void onMouseClickLeft();
	virtual void onMouseClickRight();
	float getAngle()const;
	Vector2 getPosition()const;
	Vector2 getCenterPosition()const;
	Vector2 getScale()const;
	SDL_Texture* getTexture()const;
	void setAngle(const float angle);
	void setPosition(const Vector2 position);
	void setScale(const Vector2 scale);
	void setTexture(SDL_Texture* texture);
	static void setEvent(SDL_Event _event);

	void operator=(GameObject &GameObject);
};