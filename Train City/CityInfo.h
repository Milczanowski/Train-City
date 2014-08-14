#pragma once
#include "GameObject.h"
class CityInfo:public GameObject
{
	std::string cityName;
public:
	CityInfo(const GameObject &, const std::string);
	~CityInfo();

	void draw();
	void onMouseNotOver();
};

