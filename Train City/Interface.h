#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Button.h"
#include <functional>
#include <algorithm>
#include "Train.h"
#include "Player.h"
#include "FunctionsAndDefinitions.h"

class MapElement;
class Map;
class Interface;
class Train;
class Player;


typedef void(*Function)(void);
typedef void(Interface::*InterfaceMethod)(void);
typedef void(Interface::*InterfaceTrain)(Train *);
typedef void(Train::*TrainMethod)(MapElement*);

union IndicatorFunction
{
	Function function;
	InterfaceMethod interfaceMethod;
	InterfaceTrain interfaceTrain;
	TrainMethod trainMethod;
};

union Object
{
	Interface * _interface;
	Train *train;
};

union Parametr
{
	MapElement *mapElement;
	Train *train;
};

class Button : public GameObject
{
protected:
	std::string message;
	Object object;
	IndicatorFunction indicatorFunction;
	Parametr parametr;
	int index;
	bool click;
public:
	Button();
	Button(const GameObject&, const std::string);
	Button(const GameObject&, const std::string, Function);
	Button(const GameObject&, const std::string, InterfaceMethod, Interface *);
	Button(const GameObject&, const std::string, InterfaceTrain, Interface *, Train*);
	Button(const GameObject&, const std::string, TrainMethod, Train *, MapElement*);

	virtual ~Button();
	void draw();
	void onMouseClickLeft();
	const bool wasPressed();
};

inline const bool Button::wasPressed()
{
	if(click)
	{
		click = false;
		return true;
	}

	return false;
}

typedef std::list<Button> ButtonList;

enum InterfaceState
{
	waiting = 0,
	buyingTrain = 1,
	connectsCity,
	displaysTrains,
	displaysTrainOptions,
	selectTrainTarget
};

union Target
{
	MapElement * mapElement;
	Train * train;
};



class Interface : public GameObject
{
private:
	void cityOptions();
	void buyTrain();
	void showTrains();
	void selectTrain(Train *);
	void up();
	void down();
	void trainGoTo();
	unsigned int index;
protected:
	Map * map;
	Target target;
	InterfaceState interfaceState;
	ButtonList buttonList;
	void connectMapElement();
	void addPassengerTrain();
public:
	Interface(const GameObject &, Map *);
	virtual ~Interface();
	void setTarget(MapElement *);
	void setTarget(const std::string);
	void update();
	void draw();

	const MapElement * getTarget()const;
};


inline const MapElement * Interface::getTarget()const
{
	return target.mapElement;
}







