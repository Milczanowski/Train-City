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
	//currentBurden+=value;
	//if(currentBurden>capacity)
	//{
	//	unsigned int overload = currentBurden%capacity;
	//	currentBurden = capacity;
	//	return overload;
	//}
	//return 0;
}

void PassengerTrain::unload(const unsigned int value)
{
	//int c = currentBurden;
	//if(c-value <0)
	//{
	//	unsigned int currentValue = currentBurden;
	//	currentBurden = 0;
	//	return currentValue;
	//}
	//currentBurden-=value;
	//return value;
}

