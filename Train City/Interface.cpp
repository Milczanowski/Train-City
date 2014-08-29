#include "stdafx.h"
#include "Interface.h"
#include "Button.h"



Interface::Interface(const GameObject & gameObject, Map *map) :GameObject(gameObject), map(map), target(NULL), target2(NULL), index(0), interfaceState(0)
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

	if (target != NULL)
	{
		if(target2 != NULL)
		{
			target->setConnected(target2);
			target2->setConnected(target);

			map->addRailroadTracks(RailroadTracks( target->getCenterPosition(), target2->getCenterPosition())); 

			target2=NULL;
			MapElement::setConnect(false);
		}

		switch(interfaceState)
		{
		case 2:
			{
				buttonList.clear();
				buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorTeuexture")), "Passanger", &Interface::addPassengerTrain, this));
				interfaceState = 0;
			}break;
		case -1:
			interfaceState = 0;
			break;
		}
	}
	else
	{
		if(interfaceState==0)
		{
			showTrains();
			interfaceState = -1;
		}
	}
}

void Interface::connectMapElement()
{
	if (target!=NULL)
		target->setConnect(true);
}

void Interface::setTarget(MapElement *target)
{
	if(!MapElement::getConnect())
	{
		this->target= this->target2 = target;

		if(target==NULL)
			interfaceState = 0;
		else
		refresh();
	}
}

void Interface::setTarget(const std::string name)
{
	target = map->findCity(name);
		if(target==NULL)
			interfaceState = 0;
		else
	refresh();
}

void Interface::refresh()
{
	buttonList.clear();
	if (target != NULL)
	{
		buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorTeuexture")), "Connect", &Interface::connectMapElement, this));
		buttonList.push_back(Button(GameObject(position + Vector2(10, 115), Vector2(180,100),0, Textures::getTexture("errorTexture")), "Buy Train", &Interface::buyTrain, this));
	}
	else
	{
		MapElement::setConnect(false);
	}
}

void Interface::addPassengerTrain()
{
	Player::getInstance().addTrain(new PassengerTrain(100,80,target));
}

void Interface::buyTrain()
{
	interfaceState = 2;
	MapElement::setConnect(false);
}


void Interface::showTrains()
{
	buttonList.clear();
	buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorTeuexture")), "UP", &Interface::up, this));
	int i=0, name =0;

	for(TrainList::const_iterator iter = Player::getInstance().getTrainList()->begin(); iter != Player::getInstance().getTrainList()->end(); iter++)
	{
		if(i>=index && (*iter)->isReady())
		{
			buttonList.push_back(Button(GameObject(position + Vector2(10,120+ 110*(i-index)), Vector2(180, 100), 0, Textures::getTexture("errorTeuexture")), ToString<int>(i) , &Interface::up, this));	
			if(i >= index+ 4)
				break;
		}
		i++;
	}
	buttonList.push_back(Button(GameObject(position + Vector2(10, 690), Vector2(180, 100), 0, Textures::getTexture("errorTeuexture")), "DOWN", &Interface::down, this));
}


void Interface::up()
{
	if(index + 5  <  Player::getInstance().getTrainList()->size())
		index++;

	showTrains();
}

void Interface::down()
{
	if(index>0)
		--index;

	showTrains();
}

