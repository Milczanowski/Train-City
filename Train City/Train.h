#pragma once
#include "MapElement.h"
#include "Delay.h"
#include "MapElement.h"

class MapElement;

class Train
{
protected:
	MapElement *target;
	unsigned int capacity, currentBurden;
private:
	float averageSpeed;
	Delay delay;
public:
	void goTo(MapElement *);
	const bool isReady()const;
	virtual const unsigned int load(const unsigned int)=0;
	virtual const unsigned int unload(const unsigned int)=0;
	Train(const float,const unsigned int, MapElement *);
	~Train(void);
};


class PassengerTrain :public Train
{
public:
	PassengerTrain(const float,const unsigned int, MapElement *);
	virtual ~PassengerTrain(void);
	const unsigned int load(const unsigned int);
	const unsigned int unload(const unsigned int);
};



