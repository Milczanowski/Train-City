#include "stdafx.h"
#include "Button.h"

Button::Button(const GameObject& gameObject, const std::string message) :GameObject(gameObject), message(message), index(-1),click(false)
{
}

Button::Button(const GameObject& gameObject, const std::string message, Function function) :GameObject(gameObject), message(message), index(0),click(false)
{
	indicatorFunction.function = function;
}

Button::Button(const GameObject& gameObject, const std::string message, InterfaceMethod interfaceMethod, Interface *const  _interface)
	: GameObject(gameObject), message(message), index(1), click(false)
{
	indicatorFunction.interfaceMethod = interfaceMethod;
	object._interface = _interface;
}

Button::Button(const GameObject& gameObject, const std::string message, InterfaceTrain interfaceMethod, Interface * const _interface, Train * const train)
	: GameObject(gameObject), message(message), index(2), click(false)
{
	indicatorFunction.interfaceTrain = interfaceMethod;
	object._interface = _interface;
	parametr.train =train;
}

Button::Button(const GameObject& gameObject, const std::string message, TrainMethod trainMethod, Train * const train,const unsigned int diffrence)
	: GameObject(gameObject), message(message), index(3), click(false)
{
	indicatorFunction.trainMethod = trainMethod;
	object.train = train;
	parametr.diffrence = diffrence;
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
	GraphicDevice::drawText(message, GraphicDevice::getColor(0, 0, 0, 255), position,40);
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
		if(indicatorFunction.interfaceMethod!=NULL && object._interface!=NULL)
			(object._interface->*indicatorFunction.interfaceMethod)(); 
		break;
	case 2:
		{
			if(indicatorFunction.interfaceTrain!=NULL && object._interface!=NULL)
				(object._interface->*indicatorFunction.interfaceTrain)(parametr.train);
		}break;
	case 3:
		{
			if(indicatorFunction.trainMethod!=NULL && object.train!=NULL)
				(object.train->*indicatorFunction.trainMethod)(parametr.diffrence);
		}break;
	}	
}
