#include "stdafx.h" 
#include "Product.h"


Product::Product(const std::string name, const float price, const float productionPerSecond, const float demandPerSecond, const float count) :
name(name), price(fabs(price)), productionPerSecond(fabs(productionPerSecond)), demandPerSecond(fabs(demandPerSecond)), count(count)
{
}


Product::~Product()
{
}

void Product::update()
{
	count += productionPerSecond;
	count -= demandPerSecond;
	if (count < 0)count = 0;

	if (productionPerSecond < demandPerSecond)
		price += 0.01f * price;
	else if (productionPerSecond > demandPerSecond)
		price -= 0.01f * price;
}

void Product::upgrade()
{
	productionPerSecond *= 1 + (((float)((rand() % 50) - 25)) / 100);
	demandPerSecond		*= 1 + (((float)((rand() % 50) - 25)) / 100);	
}