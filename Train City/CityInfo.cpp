#include "stdafx.h"
#include "CityInfo.h"


CityInfo::CityInfo(const GameObject &gameObject, const std::string cityName) :GameObject(gameObject), cityName(cityName)
{
}


CityInfo::~CityInfo()
{
}

void CityInfo::draw()
{
	GameObject::draw();
	GraphicDevice::drawText(cityName, GraphicDevice::getColor(0, 0, 0, 0), position+ Vector2(5,5), 16);
}

void CityInfo::onMouseNotOver()
{
	destroy = true;
}