#include "stdafx.h"
#include "City.h"


City::City(const GameObject& gameObject, std::string name) :GameObject(gameObject), name(name), cityInfo(NULL)
{
}


City::~City()
{
}

void City::onMouseOver()
{
	if (cityInfo == NULL)
		cityInfo = new CityInfo(GameObject(position, Vector2(100, 100), 0, Textures::getTexture("cityInfo.png")), name);
}

void City::draw()
{
	GameObject::draw();
	if (cityInfo != NULL)
		cityInfo->draw();
}

void City::update()
{
	GameObject::update();
	if (cityInfo != NULL)
	{
		cityInfo->update();
		if (cityInfo->getDestroy())
		{
			delete cityInfo;
			cityInfo = NULL;
		}
	}
}
