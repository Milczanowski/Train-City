#include "stdafx.h"
#include "Interface.h"


Interface::Interface(const GameObject & gameObject, Map *map) :GameObject(gameObject), map(map)
{
}


Interface::~Interface()
{
}

void Interface::draw()
{
	GameObject::draw();

	for (ButtonList::iterator iter = buttonList.begin(); iter != buttonList.end(); iter++)
		iter->draw();
}

void Interface::update()
{
	GameObject::update();

	for (ButtonList::iterator iter = buttonList.begin(); iter != buttonList.end(); iter++)
		iter->update();
}

void Interface::connectMapElement()
{
	if (target!=NULL)
		target->setConnect(true);
}

void Interface::setTarget(MapElement *target)
{
	this->target = target;
	refresh();
}

void Interface::setTarget(const std::string name)
{
	target = map->findCity(name);
	refresh();
}

void Interface::refresh()
{
	buttonList.clear();
	if (target != NULL)
	{
		buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorTexture")), "Connect", &Interface::connectMapElement, this));
	}
}


