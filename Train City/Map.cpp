#include "stdafx.h"
#include "Map.h"


Map::Map(const GameObject & gameObject, std::string fileName) :GameObject(gameObject)
{
	std::ifstream cityFile(fileName);
	if (cityFile.is_open())
	{
		while (!cityFile.eof())
		{

			std::string cityName, textureName;
			Vector2 pos, size;
			cityFile >> cityName >> textureName >> pos >> size;
			cities.push_back(City(GameObject(pos, size, 0, Textures::getTexture(textureName)), cityName));
		}
	}
	else throw GameError(fileName + " not found");
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
	for (Cities::iterator iter = cities.begin(); iter != cities.end(); iter++)
	{
		iter->update();
	}
}