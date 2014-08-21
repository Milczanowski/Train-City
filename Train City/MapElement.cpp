#include "stdafx.h"
#include "MapElement.h"


MapElement::MapElement(const GameObject& gameObject, const std::string name, const std::string connectionsListFile) :GameObject(gameObject), name(name), info(NULL)
{
	std::ifstream fileConnectionList(connectionsListFile);
	if (fileConnectionList.is_open())
	{
		while (!fileConnectionList.eof())
		{
			std::string name;
			fileConnectionList >> name;
			permittedConnections.push_back(name);
		}
	}
	else throw GameError(connectionsListFile + ": file not found(MapElement)");
}


MapElement::~MapElement()
{
}

void MapElement::onMouseOver()
{
	if (info == NULL)
	{
		Vector2 basicInfoSize = getCenterPosition() - (cityInfoSize / 2);
		if (basicInfoSize.get_X() < 200)basicInfoSize.set_X(200);
		if (basicInfoSize.get_Y() < 0)basicInfoSize.set_Y(0);
		if (basicInfoSize.get_X() + cityInfoSize.get_X() > DEFAULT_SIZE_W)basicInfoSize.set_X(DEFAULT_SIZE_W - cityInfoSize.get_X());
		//if (basicInfoSize.get_Y() + cityInfoSize.get_Y() > DEFAULT_SIZE_H)basicInfoSize.set_Y(DEFAULT_SIZE_H - cityInfoSize.get_Y());

		info = new BasicInfo(GameObject(basicInfoSize, cityInfoSize, 0, Textures::getTexture("cityInfo.png")), name);
	}
}

void MapElement::onMouseClickLeft()
{
	if (_interface != NULL)
		_interface->setTarget(this);
}

void MapElement::setConnected(MapElement *mapElement)
{
	connections.push_back(mapElement);
	permittedConnections.remove(mapElement->name);
}

Interface * MapElement::_interface = NULL;
bool MapElement::connect = false;