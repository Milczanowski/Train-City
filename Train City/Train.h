#pragma once
#include "MapElement.h"
#include "Delay.h"
#include "Button.h"

class MapElement;
class Button;
typedef std::list<Button> ButtonList;

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
	virtual const std::string getType()const = 0;
	virtual void load(unsigned int *)=0;
	virtual void unload(unsigned int *)=0;
	Train(const float,const unsigned int, MapElement *);
	~Train(void);
};


class PassengerTrain :public Train
{
public:
	PassengerTrain(const float,const unsigned int, MapElement *);
	virtual ~PassengerTrain(void);
	void load(unsigned int *);
	void unload(unsigned int *);
	const ButtonList getButtonList()const;
	const std::string getType()const ;
};

inline const std::string PassengerTrain::getType()const
{
	return "Passenger";
}


