#include "stdafx.h"
#include "Button.h"

Button::Button(const GameObject& gameObject, const std::string message) :GameObject(gameObject), message(message), index(-1),click(false)
{
}

Button::Button(const GameObject& gameObject, const std::string message, Function function) :GameObject(gameObject), message(message), index(0),click(false)
{
	indicatorFunction.function = function;
}


Button::Button(const GameObject& gameObject, const std::string message, InterfaceMethod interfaceMethod, Interface * _interface)
	: GameObject(gameObject), message(message), _interface(_interface), index(1), click(false)
{
	indicatorFunction.interfaceMethod = interfaceMethod;
}


Button::~Button()
{
}

Button::Button():GameObject(Vector2(0,0),Vector2(0,0),0,NULL),index(-1),click(false)
{
}

void Button::draw()
{
	GameObject::draw();
	GraphicDevice::drawText(message, GraphicDevice::getColor(0, 0, 0, 255), position,50);
}

void Button::onMouseClickLeft()
{
	click = true;
	switch (index)
	{
	case 0:
		if(indicatorFunction.function!=NULL)
			indicatorFunction.function();
		break;
	case 1:
		if(indicatorFunction.interfaceMethod!=NULL && _interface!=NULL)
			(_interface->*indicatorFunction.interfaceMethod)(); 
		break;
	default:
		break;
	}	
}
