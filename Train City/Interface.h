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

union IndicatorFunction
{
public:
	Function function;
	InterfaceMethod interfaceMethod;
};

class Button : public GameObject
{
protected:
	std::string message;
	Interface * _interface;
	IndicatorFunction indicatorFunction;
	int index;
	bool click;
public:
	Button();
	Button(const GameObject&, const std::string);
	Button(const GameObject&, const std::string, Function);
	Button(const GameObject&, const std::string, InterfaceMethod, Interface *);

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

class Interface : public GameObject
{
private:
	void refresh();
	void buyTrain();
	void showTrains();

	void up();
	void down();

	unsigned int index;
protected:
	Map * map;
	MapElement * target , *target2;
	int interfaceState;
	ButtonList buttonList;
	void connectMapElement();
	void addPassengerTrain();
public:
	Interface(const GameObject &, Map *);
	virtual ~Interface();
	void setTarget(MapElement *);
	void setTarget(const std::string);
	void setTarget2(MapElement *);
	void update();
	void draw();

	const MapElement * getTarget()const;
};



inline const MapElement * Interface::getTarget()const
{
	return target;
}

inline void Interface::setTarget2(MapElement * target2)
{
	this->target2 = target2;
}




