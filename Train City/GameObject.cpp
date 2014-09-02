#include "stdafx.h" 
#include "GameObject.h"

//Constructors and destructors

GameObject::GameObject(const Vector2 position, const Vector2 size, const float angle,SDL_Texture* texture):
	position(position), 
	size(size.module()), 
	angle(angle), 
	texture(texture),
	_onMouseDown(true),
	destroy(false)
{
}

GameObject::~GameObject(void)
{
}

//Functions
void GameObject::draw()const
{
	GraphicDevice::drawTexture(texture, position, size,angle); 
}

void GameObject::update()
{
	if(Mouse::checkCollision(position,size))
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
