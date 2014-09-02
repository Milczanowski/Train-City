#include "Vector2.h"
#include <SDL.h>
#include <math.h>
#include "GraphicDevice.h"
#include "Mouse.h"
#include <string.h>

#pragma once
class GameObject
{
protected:
	Vector2 position;
	Vector2 size;
	static SDL_Event _event;
	float angle;
	SDL_Texture * texture;
	bool _onMouseDown, destroy;
public:	
	GameObject(const Vector2 position, const Vector2 size, const float angle,SDL_Texture* texture);
	virtual~GameObject(void);

	virtual void draw()const;
	virtual void update();
	virtual void onMouseOver();
	virtual void onMouseNotOver();
	virtual void onMouseClickLeft();
	virtual void onMouseClickRight();

	const float	getAngle()const;
	const bool getDestroy()const;
	const Vector2 getPosition()const;
	const Vector2 getCenterPosition()const;
	const Vector2 getSize()const;
	SDL_Texture* getTexture()const;

	void setAngle(const float angle);
	void setPosition(const Vector2 position);
	void setSize(const Vector2 size);
	void setTexture(SDL_Texture* texture);
	static void setEvent(SDL_Event _event);
};

inline const bool GameObject::getDestroy()const
{
	return destroy;
}

inline const float GameObject::getAngle()const
{
	return this->angle;
}

inline const Vector2 GameObject::getPosition()const
{
	return this->position;
}

inline const Vector2 GameObject::getCenterPosition()const
{
	return this->position +(size/2);
}

inline const Vector2 GameObject::getSize()const
{
	return this->size;
}

inline SDL_Texture* GameObject::getTexture()const
{
	return this->texture;
}

inline void GameObject::setAngle(const float angle)
{
	this->angle = angle;
}

inline void GameObject::setPosition(const Vector2 position)
{
	this->position = position;
}

inline void GameObject::setSize(const Vector2 size)
{
	this->size = size;
}

inline void GameObject::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}