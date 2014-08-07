#include "stdafx.h"
#include "GameObject.h"

//Constructors and destructors
GameObject::GameObject(void):position(Vector2(0,0)),scale(Vector2(0,0)),angle(0), texture(NULL)
{
}

GameObject::GameObject(const Vector2 position, const Vector2 scale, const float angle,SDL_Texture* texture):
	position(position), 
	scale(scale.module()), 
	angle(angle), 
	texture(texture),
	_onMouseDown(true)
{
}

GameObject::~GameObject(void)
{
}

//Getters and setters
float GameObject::getAngle()const
{
	return this->angle;
}

Vector2 GameObject::getPosition()const
{
	return this->position;
}

Vector2 GameObject::getCenterPosition()const
{
	return position+(scale/2);
}

Vector2 GameObject::getScale()const
{
	return this->scale;
}

SDL_Texture* GameObject::getTexture()const
{
	return this->texture;
}

void GameObject::setAngle(const float angle)
{
	this->angle = angle;
}

void GameObject::setPosition(const Vector2 position)
{
	this->position = position;
}

void GameObject::setScale(const Vector2 scale)
{
	this->scale = scale;
}

void GameObject::setTexture(SDL_Texture* texture)
{
	this->texture = texture;
}

//Functions
void GameObject::draw()
{
	GraphicDevice::drawTexture(texture, position, scale); 
}

void GameObject::update()
{
	if(Mouse::checkCollision(position,scale))
	{
		onMouseOver();
		if(_event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(_event.button.button == SDL_BUTTON_LEFT)
			{
				if(!_onMouseDown)
				{
					onMouseClickLeft();
					_onMouseDown=true;
				}
			}
			if(_event.button.button == SDL_BUTTON_RIGHT)
			{
				onMouseClickRight();
			}
		}
		else
			_onMouseDown=false;
	}
	else
		onMouseNotOver();
}

void GameObject::onMouseOver()
{
}

void GameObject::onMouseNotOver()
{
}

void GameObject::onMouseClickLeft()
{
}

void GameObject::onMouseClickRight()
{
}

void GameObject::setEvent(SDL_Event _event)
{
	GameObject::_event=_event;
}

SDL_Event GameObject::_event;
