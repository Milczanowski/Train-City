#include "StdAfx.h"
#include "Train.h"


Train::Train(const float averageSpeed,const unsigned int capacity, MapElement * const target):averageSpeed( fabs(averageSpeed)), capacity(capacity), target(target), delay(Delay(0)), currentBurden(0)
{
}


Train::~Train(void)
{
}

void Train::goTo(MapElement * const target)
{
	float distance = target->getCenterPosition().distance(this->target->getCenterPosition());
	//this->target= target;
	delay = Delay((int)(distance/averageSpeed));
}


const bool Train::isReady()const
{
	return delay.isRedy();
}