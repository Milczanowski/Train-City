#include "stdafx.h" 
#include "Map.h"


Map::Map(const GameObject & gameObject, std::string fileName) :GameObject(gameObject),schedule(new Schedule())
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
	delete schedule;
	for(MapElements::iterator iter = mapElements.begin();iter != mapElements.end();iter++)
	{
		delete (*iter);
	}
}


Schedule * const Map::getSchedule()const
{
	return schedule;
}

void Map::draw()const
{
	GameObject::draw();

	for(RailroadTracksList::const_iterator iter = railroadTrackList.begin(); iter != railroadTrackList.end(); iter++)
	{
		iter->draw();
	}
	Player::getInstance().drawTrains();

	for (MapElements::const_iterator iter = mapElements.begin(); iter != mapElements.end(); iter++)
	{
		(*iter)->draw();
	}
}


void Map::update()
{	
	GameObject::update();
	for (MapElements::iterator iter = mapElements.begin(); iter != mapElements.end(); iter++)
	{
		(*iter)->update();
	}

	schedule->update();
}

void Map::onMouseClickLeft()
{

}

std::ostream & operator<< (std::ostream & v, const Map & map)
{
	v<<map.railroadTrackList.size()<<std::endl;
	for(RailroadTracksList::const_iterator iter = map.railroadTrackList.begin(); iter != map.railroadTrackList.end(); iter++)
	{
		v<<(*iter);
	}
	return v;
	
}
std::istream & operator>> (std::istream & v, Map & map)
{
	unsigned int i;
	v>>i;

	for(;i>0;--i)
	{
		Vector2 start, end;
		v>>start>>end;
		map.addRailroadTracks(RailroadTracks(start,end));
	}

	return v;
}

void Map::onMouseClickRight()
{
	MapElement::setState(notSelect);

	if (MapElement::_interface != NULL)
		MapElement::_interface->setTarget(NULL);
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