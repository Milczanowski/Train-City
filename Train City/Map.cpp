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
				cities.push_back(City(MapElement(GameObject(pos, size, 0, Textures::getTexture(textureName)), cityName, connectionsListFile), productsFileName));
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
	for (Cities::iterator iter = cities.begin(); iter != cities.end(); iter++)
	{
		iter->draw();
	}
}


void Map::update()
{	
	GameObject::update();
	for (Cities::iterator iter = cities.begin(); iter != cities.end(); iter++)
	{
		iter->update();
	}
}

void Map::onMouseClickLeft()
{
	if (MapElement::_interface != NULL)
		MapElement::_interface->setTarget(NULL);
}