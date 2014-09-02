#include "StdAfx.h"
#include "PassengerTrain.h"


PassengerTrain::PassengerTrain(const float averageSpeed,const unsigned int capacity, MapElement *const target):Train(averageSpeed, capacity,target)
{
	
}


PassengerTrain::~PassengerTrain(void)
{
}

void PassengerTrain::load(const unsigned int  value)
{
	for(unsigned int i = 0; i< capacity; ++i)
	{
		if(getProduct("People")->getCount()>0)
		{
			getProduct("People")->remove(false);
		}
	}
}

void PassengerTrain::update()
{
	if(delay.isRedy())
	{
		currentBurden= 0;
		load(capacity);
	}
}

void PassengerTrain::unload(const unsigned int value)
{
}

