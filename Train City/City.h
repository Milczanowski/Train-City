#pragma once
#include "GameObject.h"
#include "CityInfo.h"
#include "Textures.h"
class City: public GameObject
{
private:
	std::string name;
	CityInfo *cityInfo;
public:
	City(const GameObject&, std::string);
	~City();
	void onMouseOver();
	void draw();
	void update();
};

