#pragma once
#include "GameObject.h"
#include "Textures.h"
#include <list>
#include <fstream>
#include "Interface.h"
#include "CityInfo.h"
#include "ProductsManager.h"

class Interface;
class BasicInfo;
class Product;
typedef std::list<Product> Products;

enum MapElementSelectState
{
	notSelect =1,
	select =2,
	conecting=4,
	routing=8
};

inline const MapElementSelectState operator|(MapElementSelectState v1, MapElementSelectState v2)
{
	return static_cast<MapElementSelectState>(static_cast<int>(v1)|static_cast<int>(v2));
}

class MapElement : public GameObject
{	
	typedef std::list<std::string> StringList;

protected:
	SDL_Texture* selectTexture;
	std::string name;
	BasicInfo * info;
	StringList permittedConnections;
	StringList connections;
	static MapElementSelectState selectState; 
public:	
	static Interface * _interface;


	MapElement(const GameObject& , const std::string, const std::string);
	virtual ~MapElement();

	const std::string getName()const;
	void update();
	void draw()const;

	void Select();
	void UnSelect();
	void onMouseOver();
	void onMouseClickLeft();
	void setConnected(MapElement *const);
	static void setState(const MapElementSelectState);
	static const MapElementSelectState getState(); 
};

class ProductsManager
{
private:
	Delay refreshDelay, upgradeDelay;		
public:	
	ProductsManager(const Delay &, const Delay &);
	~ProductsManager();
	void update(Products * products);
};

class City : public MapElement
{
private:
	Products products;
	ProductsManager productsManager;
public:
	City(const MapElement&, const std::string);
	virtual ~City();
	const Products::iterator getProduct(const std::string);
	void onMouseOver();
	void draw()const;
	void update();
};




