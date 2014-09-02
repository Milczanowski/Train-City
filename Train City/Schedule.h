#pragma once
#include "PassengerTrain.h"
#include "MapElement.h"

class PassengerTrain;
class MapElement;
class Map;

class Set
{
private:
	PassengerTrain *train;
	MapElement *target, *target2;
	bool direction;
public:
	Set(PassengerTrain * const train, MapElement * const target, MapElement * const target2):train(train), target(target), target2(target2), direction(true){}
	void go();
	PassengerTrain * const getPassengerTrain()const{return train;}
};

typedef std::list<Set> SetList;

class Schedule
{
private:
	SetList setList;
public:
	Schedule(void);
	~Schedule(void);

	void add(PassengerTrain * const, MapElement * const, MapElement * const);
	void update();
};

