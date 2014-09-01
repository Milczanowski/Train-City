#include "stdafx.h"
#include "City.h"


City::City(const MapElement& MapElement,  const std::string productsFileName) : MapElement(MapElement) ,  productsManager(ProductsManager(Delay(1000), Delay(10000)))
{
	std::ifstream productsFile(productsFileName);
	if (productsFile.is_open())
	{
		while (!productsFile.eof())
		{
			std::string name;
			float price, productionPerSecond, demandPerSecond, count;
			productsFile >> name >> price >> productionPerSecond >> demandPerSecond >> count;
			products.push_back(Product(name, price, productionPerSecond, demandPerSecond, count));
		}
	}
	else throw GameError(productsFileName + ":file not found(Products)");	

}


const Products::iterator City::getProduct(const std::string name)
{
	for(Products::iterator iter = products.begin(); iter!=products.end();iter++)
	{
		if((*iter).getName()== name)
			return iter;
	}
	throw GameError("Product not fount : ", name +"in City: "+this->name);
}



City::~City()
{
}

void City::onMouseOver()
{
	if (info == NULL && selectState == notSelect)
	{
		Vector2 cityInfoPos = getCenterPosition() - (cityInfoSize / 2);
		if (cityInfoPos.get_X() < 200)cityInfoPos.set_X(200);
		if (cityInfoPos.get_Y() < 0)cityInfoPos.set_Y(0);
		if (cityInfoPos.get_X() + cityInfoSize.get_X() > DEFAULT_SIZE_W)cityInfoPos.set_X(DEFAULT_SIZE_W - cityInfoSize.get_X());
		//if (cityInfoPos.get_Y() + cityInfoSize.get_Y() > DEFAULT_SIZE_H)cityInfoPos.set_Y(DEFAULT_SIZE_H - cityInfoSize.get_Y());

		info = new CityInfo(BasicInfo(GameObject(cityInfoPos, cityInfoSize, 0, Textures::getTexture("cityInfo.png")), name), &products);
	}
}

void City::draw()
{
	MapElement::draw();
	if (info != NULL)
		info->draw();
}

void City::update()
{
	MapElement::update();
	if (info != NULL)
	{
		info->update();
		if (info->getDestroy())
		{
			delete info;
			info = NULL;
		}
	}

	productsManager.update(&products);
}


