#include "stdafx.h" 
#include "Map.h"


Map::Map(const GameObject & gameObject, std::string fileName) :GameObject(gameObject)
{
	std::ifstream cityFile(fileName);
	if (cityFile.is_open())
	{
		while (!cityFile.eof())
		{

			std::string textureName, cityName, connectionsListFile, productsFileName;
			Vector2 pos, size;
			cityFile >> pos >> size >> textureName >> cityName >> connectionsListFile >> productsFileName;
			try
			{
				mapElements.push_back(new City(MapElement(GameObject(pos, size, 0, Textures::getTexture(textureName)), cityName, connectionsListFile), productsFileName));
			}
			catch (GameError & gameError)
			{
				gameError.generateErrorLog(errorFile);
			}
		}
	}
	else throw GameError(fileName + ":file not found(Cities)");
}


Map::~Map()
{
}


void Map::draw()
{
	GameObject::draw();
	for (MapElements::iterator iter = mapElements.begin(); iter != mapElements.end(); iter++)
	{
		(*iter)->draw();
	}

	for(RailroadTracksList::const_iterator iter = railroadTrackList.begin(); iter != railroadTrackList.end(); iter++)
	{
		iter->draw();
	}
}


void Map::update()
{	
	GameObject::update();
	for (MapElements::iterator iter = mapElements.begin(); iter != mapElements.end(); iter++)
	{
		(*iter)->update();
	}
}

void Map::onMouseClickLeft()
{
	if (MapElement::_interface != NULL)
		MapElement::_interface->setTarget(NULL);
}

void Map::onMouseClickRight()
{
	MapElement::setConnect(false);
}

MapElement * Map::findCity(const std::string name)const
{
	for (MapElements::const_iterator iter = mapElements.begin(); iter != mapElements.end(); iter++)
	{
		if ((*iter)->getName() == name)
			 return (*iter);
	}
	return NULL;
}