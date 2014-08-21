#include "stdafx.h" 
#include "ProductsManager.h"


ProductsManager::ProductsManager(const Delay & refreshDelay, const Delay &upgradeDelay) : refreshDelay(refreshDelay), upgradeDelay(upgradeDelay)
{
}


ProductsManager::~ProductsManager()
{
}

void ProductsManager::update(Products * products)
{
	if (refreshDelay.isRedy())
	{
		refreshDelay.Restart();
		for (Products::iterator iter = products->begin(); iter != products->end(); iter++)
			iter->update();	
	}

	if (upgradeDelay.isRedy())
	{
		upgradeDelay.Restart();
		for (Products::iterator iter = products->begin(); iter != products->end(); iter++)
			iter->upgrade();
	}


}
