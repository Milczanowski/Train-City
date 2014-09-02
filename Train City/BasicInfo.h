#pragma once
#include "GameObject.h"
#include "MapElement.h"
#include "ProductsManager.h"
#include <list>

class Product;
typedef std::list<Product> Products;

class BasicInfo :public GameObject
{
protected:
	std::string name;

public:
	BasicInfo(const GameObject &, const std::string);
	virtual ~BasicInfo();

	void draw();
	void onMouseNotOver();
	void onMouseClickLeft();
};


class CityInfo :public BasicInfo
{
private:
	Products * products;
public:
	CityInfo(const BasicInfo &, Products *);
	~CityInfo();

	void draw();
};