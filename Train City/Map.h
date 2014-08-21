#pragma once
#include "City.h"
#include <list>
#include <fstream>
#include "MapElement.h"

class City;
class MapElement;

typedef std::list<MapElement*> MapElements;


class Map : public GameObject
{	
private:
	MapElements mapElements;
public:
	Map(const GameObject &, std::string );
	~Map();

	void draw();
	void update();
	void onMouseClickLeft();
	MapElement * findCity(const std::string)const;
};

