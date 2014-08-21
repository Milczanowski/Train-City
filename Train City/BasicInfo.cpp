#include "stdafx.h"
#include "BasicInfo.h"


BasicInfo::BasicInfo(const GameObject &gameObject, const std::string name) :GameObject(gameObject), name(name)
{
}


BasicInfo::~BasicInfo()
{
}


void BasicInfo::onMouseNotOver()
{
	destroy = true;
}


void BasicInfo::draw()
{
	GameObject::draw();
	GraphicDevice::drawText(name, GraphicDevice::getColor(0, 0, 0, 0), position + Vector2(5, 5), 20);
}

void BasicInfo::onMouseClickLeft()
{
	if (MapElement::_interface != NULL)
		MapElement::_interface->setTarget(name);
}

