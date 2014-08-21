#include "stdafx.h"
#include "CityInfo.h"


CityInfo::CityInfo(const BasicInfo &basicInfo, Products * products) : BasicInfo(basicInfo), products(products)
{
}


CityInfo::~CityInfo()
{
}

void CityInfo::draw()
{
	GameObject::draw();
	GraphicDevice::drawText(name, GraphicDevice::getColor(0, 0, 0, 0), position	+ Vector2(5,5), 20);
	GraphicDevice::drawText("Name:       Price:             P/D:       Number:", GraphicDevice::getColor(0, 0, 0, 0), position + Vector2(5, 25), 16);
	if (products != NULL)
	{
		int i = 1;
		for (Products::iterator iter = products->begin(); iter != products->end(); iter++)
		{
			iter->draw(position + Vector2(5 ,25 + 20.0f*i  ) , 17);
			++i;
		}
	}
}
