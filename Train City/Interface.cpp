#include "stdafx.h"
#include "Interface.h"
#include "Button.h"



Interface::Interface(const GameObject & gameObject, Map * const map) :GameObject(gameObject), map(map), index(0), interfaceState(waiting)
{
	showTrains();
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

	switch(interfaceState)
	{
	case buyingTrain:
		{
			buyTrain();
		}break;
	case displaysTrainOptions:
		{
			selectTrain(target.train);
		}break;
	}
}	

void Interface::trainGoTo()
{
	interfaceState = selectTrainTarget;
	MapElement::setState(select|routing);
}

void Interface::connectMapElement()
{
	if (target.mapElement!=NULL)
	{
		target.mapElement->setState(conecting|select);
		interfaceState = connectsCity;
	}
}

void Interface::setTarget(MapElement * const target)
{
	
	if(target!=NULL)
	{
		switch(interfaceState)
		{
		case waiting:
			{
				this->target.mapElement = target;
				cityOptions();
			}break;
		case connectsCity:
			{
				this->target.mapElement->setConnected(target);
				target->setConnected(this->target.mapElement);

				map->addRailroadTracks(RailroadTracks(this->target.mapElement->getCenterPosition(),target->getCenterPosition()));
				this->target.mapElement->setState(notSelect);
				interfaceState = waiting;
			}break;
		case selectTrainTarget:
			{
				this->target.train->goTo(NULL);
			}break;
		}
	}
	else
	{
		interfaceState = waiting;
		showTrains();
	}
}

void Interface::setTarget(const std::string name)
{
	setTarget(map->findCity(name));
}

void Interface::cityOptions()
{
	buttonList.clear();
	if (target.mapElement != NULL)
	{
		buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorImage")), "Connect", &Interface::connectMapElement, this));
		buttonList.push_back(Button(GameObject(position + Vector2(10, 115), Vector2(180,100),0, Textures::getTexture("errorImage")), "Buy Train", &Interface::buyTrain, this));
	}
	else
	{
		MapElement::setState(notSelect);
	}
}

void Interface::addPassengerTrain()
{
	if(target.mapElement!=NULL)
	{		
		MapElement::setState(notSelect);
		Player::getInstance().addTrain(new PassengerTrain(100,80,target.mapElement));
	}
}

void Interface::buyTrain()
{
	if(target.mapElement!=NULL)
	{
		switch(interfaceState)
		{
		case buyingTrain:
			{
				interfaceState = waiting;
				buttonList.clear();
				buttonList.push_back(Button(GameObject(position+Vector2(10,10),Vector2(150,100),0,Textures::getTexture("errorImage")),"Passanger", &Interface::addPassengerTrain,this)); 
			}break;
		default:
			{
				interfaceState = buyingTrain;
				target.mapElement->setState(notSelect);
			}break;
		}
	}
}

void Interface::showTrains()
{
	buttonList.clear();
	buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("errorImage")), "UP", &Interface::up, this));
	int i=0, name =0;

	for(TrainList::const_iterator iter = Player::getInstance().getTrainList()->begin(); iter != Player::getInstance().getTrainList()->end(); iter++)
	{
		if(i>=(int)index && (*iter)->isReady())
		{
			buttonList.push_back(Button(GameObject(position + Vector2(10,120+ 110.0f*(i-index)), Vector2(180, 100), 0, Textures::getTexture("errorImage")), ToString<int>(i)+(*iter)->getType() , &Interface::selectTrain, this, *iter));	
			if(i >= (int)index+ 4)
				break;
		}
		i++;
	}
	buttonList.push_back(Button(GameObject(position + Vector2(10, 690), Vector2(180, 100), 0, Textures::getTexture("errorImage")), "DOWN", &Interface::down, this));
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

void Interface::selectTrain(Train * const train)
{
	if(train!=NULL)
	{
		switch(interfaceState)
		{
		case displaysTrainOptions:
			{
				buttonList.clear();
				target.train = train;
				interfaceState = waiting;
				buttonList.push_back(Button(GameObject(position+Vector2(10,10),Vector2(150,100),0,Textures::getTexture("errorImage")),"Go To",&Interface::trainGoTo,this));
				if(typeid(train)!=typeid(PassengerTrain))
				{
				
				}
			}break;
		default:
			{
				interfaceState = displaysTrainOptions;
			}break;
		}
		
	}
}
