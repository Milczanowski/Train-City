#pragma once
#include "Delay.h"
#include "Product.h"

class ProductsManager
{
private:
	Delay refreshDelay, upgradeDelay;		
public:	
	ProductsManager(const Delay &, const Delay &);
	~ProductsManager();
	void update(Products * products);
};

