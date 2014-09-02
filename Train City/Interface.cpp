#include "stdafx.h"
#include "Interface.h"
#include "Button.h"

Interface::Interface(const GameObject & gameObject, Map * const map) :GameObject(gameObject), index(0), interfaceState(waiting), train(NULL), mapElement(NULL),map(map)
{
	showTrains();
}

Interface::~Interface()
{
}

void Interface::draw()const
{
	GameObject::draw();

	for (ButtonList::const_iterator iter = buttonList.begin(); iter != buttonList.end(); iter++)
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
			selectTrain(train);
		}break;
	case waiting:
		{
			if(mapElement!=NULL && train!=NULL)
			{
					mapElement->onMouseOver();
			}
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
	if (mapElement!=NULL)
	{
		mapElement->setState(conecting|select);
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
				this->mapElement = target;
				cityOptions();
			}break;
		case connectsCity:
			{
				train =NULL;
				this->mapElement->setConnected(target);
				target->setConnected(this->mapElement);
				Player::getInstance().removeCash((unsigned int)this->mapElement->getCenterPosition().distance(target->getCenterPosition()));
				map->addRailroadTracks(RailroadTracks(this->mapElement->getCenterPosition(),target->getCenterPosition()));
				this->mapElement->setState(notSelect);
				interfaceState = waiting;

			}break;
		case selectTrainTarget:
			{
				this->train->goTo(target);
				MapElement::setState(notSelect);
				interfaceState = waiting; 
				train = NULL;
				mapElement = NULL;
				showTrains();
			}break;
		case trainPlying:
			{
				if(typeid(*train)==typeid(PassengerTrain))
				{
					map->getSchedule()->add(dynamic_cast<PassengerTrain*>(train),mapElement, target);
					MapElement::setState(notSelect);
					interfaceState = waiting; 
					train = NULL;
					mapElement = NULL;
					showTrains();
				}
			}break;
		}
	}
	else
	{
		mapElement= NULL;
		train = NULL;
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
	if (mapElement != NULL)
	{
		buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("button.bmp")), "Connect", &Interface::connectMapElement, this));
		buttonList.push_back(Button(GameObject(position + Vector2(10, 115), Vector2(180,100),0, Textures::getTexture("button.bmp")), "Buy Train", &Interface::buyTrain, this));
	}
	else
	{
		MapElement::setState(notSelect);
	}
}

void Interface::addPassengerTrain()
{
	if(mapElement!=NULL)
	{		
		MapElement::setState(notSelect);
		Player::getInstance().addTrain(new PassengerTrain(0.05f,80,mapElement));
		Player::getInstance().removeCash(500);
	}
}

void Interface::addCoalTrain()
{
	if(mapElement!=NULL)
	{		
		MapElement::setState(notSelect);
		Player::getInstance().addTrain(new FreightTrain<TemplateVariables::coal,TemplateVariables::coalTrain>(0.01f,100,mapElement));
		Player::getInstance().removeCash(800);
	}
}

void Interface::addCarTrain()
{
	if(mapElement!=NULL)
	{		
		MapElement::setState(notSelect);
		Player::getInstance().addTrain(new FreightTrain<TemplateVariables::car,TemplateVariables::carTrain>(0.025f,100,mapElement));
		Player::getInstance().removeCash(900);
	}
}

void Interface::addTankerTrain()
{
	if(mapElement!=NULL)
	{		
		MapElement::setState(notSelect);
		Player::getInstance().addTrain(new FreightTrain<TemplateVariables::oil,TemplateVariables::tankerTrain>(0.03f,100,mapElement));
		Player::getInstance().removeCash(1100);
	}
}

void Interface::buyTrain()
{
	if(mapElement!=NULL)
	{
		switch(interfaceState)
		{
		case buyingTrain:
			{
				interfaceState = waiting;
				buttonList.clear();
				buttonList.push_back(Button(GameObject(position+Vector2(10,10),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Passanger", &Interface::addPassengerTrain,this)); 
				buttonList.push_back(Button(GameObject(position+Vector2(10,120),Vector2(180,100),0,Textures::getTexture("button.bmp")),TemplateVariables::tankerTrain, &Interface::addTankerTrain,this)); 
				buttonList.push_back(Button(GameObject(position+Vector2(10,230),Vector2(180,100),0,Textures::getTexture("button.bmp")),TemplateVariables::carTrain, &Interface::addCarTrain,this)); 
				buttonList.push_back(Button(GameObject(position+Vector2(10,340),Vector2(180,100),0,Textures::getTexture("button.bmp")),TemplateVariables::coalTrain, &Interface::addCoalTrain,this)); 
			}break;
		default:
			{
				interfaceState = buyingTrain;
				mapElement->setState(notSelect);
			}break;
		}
	}
}

void Interface::showTrains()
{
	buttonList.clear();
	buttonList.push_back(Button(GameObject(position + Vector2(10, 10), Vector2(180, 100), 0, Textures::getTexture("button.bmp")), "UP", &Interface::up, this));
	int i=0, name =0;
	for(TrainList::iterator iter = Player::getInstance().beginTrainList(); iter != Player::getInstance().endTrainList(); iter++)
	{
		if(i>=(int)index && (*iter)->isReady())
		{
			buttonList.push_back(Button(GameObject(position + Vector2(10,110+ 105.0f*(name)), Vector2(180, 100), 0, Textures::getTexture("button.bmp")), ToString<int>(i)+(*iter)->getType() , &Interface::selectTrain, this, (*iter)->get()));	
			name++;
			if(i >= (int)index+ 4)
				break;
		}
		i++;
	}
	buttonList.push_back(Button(GameObject(position + Vector2(10, 640), Vector2(180, 100), 0, Textures::getTexture("button.bmp")), "DOWN", &Interface::down, this));
}

void Interface::up()
{
	if(index + 5  <  Player::getInstance().getTrainList().size())
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
				this->mapElement = train->getTarget();
				interfaceState = waiting;
				buttonList.push_back(Button(GameObject(position+Vector2(10,10),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Go To",&Interface::trainGoTo,this));
				if(typeid(*train)!=typeid(PassengerTrain))
				{
					buttonList.push_back(Button(GameObject(position+Vector2(10,120),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Buy", &Train::load,train, 5)); 
					buttonList.push_back(Button(GameObject(position+Vector2(10,230),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Sell", &Train::unload,train, 5)); 
				}
				else
				{
					buttonList.push_back(Button(GameObject(position+Vector2(10,120),Vector2(180,100),0,Textures::getTexture("button.bmp")),"Plying", &Interface::trainSetPlying, this)); 
				}
			}break;
		default:
			{
				this->train = train;
				interfaceState = displaysTrainOptions;
			}break;
		}
		
	}
}

void Interface::trainSetPlying()
{
	if(train!=NULL & mapElement!=NULL)
	{
		interfaceState=trainPlying;
		MapElement::setState(select|routing);
	}
}