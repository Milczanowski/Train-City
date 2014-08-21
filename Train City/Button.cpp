#include "stdafx.h"
#include "Button.h"


Button::Button(const GameObject& gameObject, const std::string message, Function function) :GameObject(gameObject), message(message), function(function), index(0)
{
}

Button::Button(const GameObject& gameObject, const std::string message, InterfaceMethod interfaceMethod, Interface * _interface)
	: GameObject(gameObject), message(message), interfaceMethod(interfaceMethod), _interface(_interface), index(1)
{

}


Button::~Button()
{
}

Button::Button():GameObject(Vector2(0,0),Vector2(0,0),0,NULL),index(-1)
{
}

void Button::draw()
{
	GameObject::draw();
	GraphicDevice::drawText(message, GraphicDevice::getColor(0, 0, 0, 255), position,50);
}

void Button::onMouseClickLeft()
{
	switch (index)
	{
	case 0:
		function();
		break;
	case 1:
		(_interface->*interfaceMethod)(); 
	default:
		break;
	}	
}
