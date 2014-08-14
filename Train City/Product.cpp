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

	price += (productionPerSecond < demandPerSecond) ? 0.05f * price : -0.05f * price;
}