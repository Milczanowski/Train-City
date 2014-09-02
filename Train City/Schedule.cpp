#include "StdAfx.h"
#include "Schedule.h"


Schedule::Schedule(void)
{
}


Schedule::~Schedule(void)
{
}


void Schedule::add(PassengerTrain * const train, MapElement * const target, MapElement * const target2)
{
	setList.push_back(Set(train, target, target2));
}

void Schedule::update()
{
	for(SetList::iterator iter = setList.begin();iter!=setList.end();iter++)
	{
		if((*iter).getPassengerTrain()->isReady())
		{
			(*iter).go();
		}
	}
}



void Set::go()
{
	if(train!=NULL)
	{
		train->load(false);
		(direction)? train->goTo(target2) : train->goTo(target);			
		direction= !direction;
	}
}