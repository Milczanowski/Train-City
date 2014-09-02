#pragma once
#include "GraphicDevice.h"
#include <list>
#include "Player.h"

class Player;

class Product
{
private:
	std::string name;
	float price, productionPerSecond, demandPerSecond, count;
	void updatePrice();
public:
	Product(const std::string, const float, const float,const float, const float);
	~Product();

	const std::string getName()const;
	const float getPrice()const;
	const float getCount()const;
	void add();
	void remove(const bool);
	void update();
	void upgrade();
	void draw(const Vector2 &, const float)const;
};


