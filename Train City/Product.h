#pragma once
#include "GraphicDevice.h"
#include <list>


class Product
{
private:
	std::string name;
	float price, productionPerSecond, demandPerSecond, count;
public:
	Product(const std::string, const float, const float,const float, const float);
	~Product();

	const std::string getName()const;
	const float getPrice()const;
	const float getCount()const;
	void update();
	void upgrade();
	void draw(const Vector2 &, const float)const;
};

typedef std::list<Product> Products;


inline const std::string Product::getName()const
{
	return name;
}

inline const float Product::getPrice()const
{
	return price;
}
inline const float Product::getCount()const
{
	return count;
}

inline void Product::draw(const Vector2 & position, const float size)const
{	
	GraphicDevice::drawText(name, GraphicDevice::getColor(0, 0, 0, 255), position, size);	
	GraphicDevice::drawText(ToString<float>(price)+"$", GraphicDevice::getColor(0, 0, 0, 255), position+Vector2(60,0), size);
	GraphicDevice::drawText(ToString<float>(productionPerSecond / demandPerSecond), GraphicDevice::getColor(0, 0, 0, 275), position + Vector2(165, 0), size);
	GraphicDevice::drawText(ToString<float>(count), GraphicDevice::getColor(0, 0, 0, 255), position + Vector2(220, 0), size);
}


