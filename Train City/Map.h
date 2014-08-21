#pragma once
#include "City.h"
#include <list>
#include <fstream>

class City;

class Map : public GameObject
{
	typedef std::list<City> Cities;
private:
	Cities cities;
public:
	Map(const GameObject &, std::string );
	~Map();

	void draw();
	void update();
	void onMouseClickLeft();
};

