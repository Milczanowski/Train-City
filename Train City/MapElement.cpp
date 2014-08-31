#include "stdafx.h"
#include "MapElement.h"


MapElement::MapElement(const GameObject& gameObject, const std::string name, const std::string connectionsListFile) :GameObject(gameObject), name(name), info(NULL), selectTexture(NULL)
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
	if (info == NULL && selectState==waiting)
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
	if (selectTexture != NULL)
		_interface->setTarget(this);
}

void MapElement::setConnected(MapElement *mapElement)
{
	if (mapElement != NULL)
	{		
		connections.push_back(mapElement->getName());
		permittedConnections.remove(mapElement->name);
		selectState=  (MapElementSelectState)(selectState| ~select);
		UnSelect();
	}
}

void MapElement::update()
{
	GameObject::update();

	switch(selectState)
	{
	case (6):
		{
			if((std::find(permittedConnections.begin(), permittedConnections.end(), _interface->getTarget()->getName())) !=  permittedConnections.end())
				Select();
		}break;
	case(10):
		{
			if((std::find(connections.begin(),connections.end(), _interface->getTarget()->getName())) != connections.end())
				Select();
		}break;
	}

	if((selectState & notSelect)==notSelect)
		UnSelect();
}

void MapElement::draw()
{
	if (selectTexture != NULL)
		GraphicDevice::drawTexture(selectTexture, position - Vector2(10, 10), size + Vector2(20, 20));
	GameObject::draw();
}

Interface * MapElement::_interface = NULL;
MapElementSelectState MapElement::selectState = notSelect;