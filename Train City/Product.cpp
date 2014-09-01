#include "stdafx.h" 
#include "Product.h"


Product::Product(const std::string name, const float price, const float productionPerSecond, const float demandPerSecond, const float count) :
name(name), price(fabs(price)), productionPerSecond(fabs(productionPerSecond)), demandPerSecond(fabs(demandPerSecond)), count(count)
{
}


Product::~Product()
{
}

void Product::updatePrice()
{
	if (productionPerSecond < demandPerSecond)
		price += 0.01f * price;
	else if (productionPerSecond > demandPerSecond)
		price -= 0.01f * price;
}

void Product::add()
{
	count++;
	Player::getInstance().addCash((unsigned int)price);
	updatePrice();
}

void Product::remove()
{
	if(count >0)
	{
		count--;
		Player::getInstance().removeCash((unsigned int)price);
		updatePrice();
	}
}

 const std::string Product::getName()const
{
	return name;
}

 const float Product::getPrice()const
{
	return price;
}
 const float Product::getCount()const
{
	return count;
}

 void Product::draw(const Vector2 & position, const float size)const
{	
	GraphicDevice::drawText(name, GraphicDevice::getColor(0, 0, 0, 255), position, size);	
	GraphicDevice::drawText(ToString<float>(price)+"$", GraphicDevice::getColor(0, 0, 0, 255), position+Vector2(60,0), size);
	GraphicDevice::drawText(ToString<float>(productionPerSecond / demandPerSecond), GraphicDevice::getColor(0, 0, 0, 275), position + Vector2(165, 0), size);
	GraphicDevice::drawText(ToString<float>(count), GraphicDevice::getColor(0, 0, 0, 255), position + Vector2(220, 0), size);
}


void Product::update()
{
	count += productionPerSecond;
	count -= demandPerSecond;
	if (count < 0)count = 0;
	updatePrice();
}

void Product::upgrade()
{
	productionPerSecond *= 1 + (((float)((rand() % 50) - 25)) / 100);
	demandPerSecond		*= 1 + (((float)((rand() % 50) - 25)) / 100);	
}