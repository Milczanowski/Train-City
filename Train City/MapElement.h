#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <list>
#include <fstream>
#include "Interface.h"
#include "CityInfo.h"
#include "ProductsManager.h"

class Interface;
class BasicInfo;

class MapElement : public GameObject
{	
	typedef std::list<std::string> StringList;
	typedef std::list<MapElement *> ConnectionsList;

protected:
	SDL_Texture* markTexture;
	std::string name;
	BasicInfo * info;
	StringList permittedConnections;
	ConnectionsList connections;
	static bool connect;
public:	
	static Interface * _interface;


	MapElement(const GameObject& , const std::string, const std::string);
	virtual ~MapElement();

	const std::string getName()const;
	void update();
	void draw();

	void onMouseOver();
	void onMouseClickLeft();
	void setConnected(MapElement *);
	static void setConnect(const bool);
};


inline void MapElement::setConnect(const bool value)
{
	MapElement::connect = value;
}

inline const std::string MapElement::getName()const
{
	return name;
}


class City : public MapElement
{
private:
	Products products;
	ProductsManager productsManager;
public:
	City(const MapElement&, const std::string);
	virtual ~City();

	void onMouseOver();
	void draw();
	void update();
};
