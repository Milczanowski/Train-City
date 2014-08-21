#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Button.h"
#include <functional>
#include <algorithm>

class MapElement;
class Map;
class Interface;

typedef void(*Function)(void);
typedef void(Interface::*InterfaceMethod)(void);

class Button : public GameObject
{
protected:
	std::string message;
	Function function;
	Interface * _interface;
	InterfaceMethod interfaceMethod;
	int index;
public:
	Button();
	Button(const GameObject&, const std::string, Function);
	Button(const GameObject&, const std::string, InterfaceMethod, Interface *);

	virtual ~Button();
	void draw();
	void onMouseClickLeft();
	
};

typedef std::list<Button> ButtonList;

class Interface : public GameObject
{
private:
	void refresh();

protected:
	Map * map;
	MapElement * target , *target2;
	ButtonList buttonList;
	void connectMapElement();
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




