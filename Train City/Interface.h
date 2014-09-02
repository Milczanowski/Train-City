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
typedef void(Interface::*InterfaceTrain)(Train *const);
typedef void(Train::*TrainMethod)(unsigned int);

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
	unsigned int diffrence;
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
	Button(const GameObject&, const std::string, InterfaceMethod, Interface *const);
	Button(const GameObject&, const std::string, InterfaceTrain, Interface *const, Train*const);
	Button(const GameObject&, const std::string, TrainMethod, Train *const, const unsigned int);

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
	selectTrainTarget,
	trainPlying
};


class Interface : public GameObject
{
private:
	void cityOptions();
	void buyTrain();
	void showTrains();
	void selectTrain(Train * const);
	void up();
	void down();
	void trainSetPlying();
	void trainGoTo();
	void connectMapElement();
	void addPassengerTrain();
	void addTankerTrain();
	void addCoalTrain();
	void addCarTrain();
	unsigned int index;
protected:
	Map * map;
	MapElement * mapElement;
	Train * train;
	InterfaceState interfaceState;
	ButtonList buttonList;
public:
	Interface(const GameObject &);

	virtual ~Interface();
	void setTarget(MapElement *const);
	void setTarget(const std::string);
	void update();
	void draw();
	void setMapPionter(Map * const);
	void addButton(SDL_Texture *,  const std::string,  Function);
	const MapElement * const getTarget()const;
};


inline const MapElement * const Interface::getTarget()const
{
	return mapElement;
}

inline void Interface::addButton(SDL_Texture * texture  ,const std::string message, Function function)
{
	buttonList.push_back(Button(GameObject(position+ Vector2(10.0f,10.0f+ 110*buttonList.size()),Vector2(180.0f,100.0f),0,texture),message,function));
}







