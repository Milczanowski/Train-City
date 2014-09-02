#include "stdafx.h"
#include "Player.h"


Player::Player(void):cash(1000)
{

}

Player::~Player(void)
{
	for(TrainList::iterator iter = trainList.begin(); iter!=trainList.end();iter++)
		delete (*iter);
}
void Player::drawTrains()const
{
	for(TrainList::const_iterator iter = trainList.begin();iter!=trainList.end();iter++)
		(*iter)->draw();
}

void Player::drawCash(const Vector2 & position, const float textSize )const
{
	if(cash>0)
		GraphicDevice::drawText(ToString(cash)+"$",GraphicDevice::getColor(255,255,255,255),position, textSize);
	else
		GraphicDevice::drawText(ToString(cash)+"$",GraphicDevice::getColor(255,0,0,255),position, textSize);
}

 void Player::addCash(const unsigned int value)
{
	cash+=value;
}

 void Player::removeCash(const unsigned int value)
{
	cash-=value;
}

 const TrainList Player::getTrainList()const
{
	return trainList;
}

 Player & Player::getInstance()
{
	if(instance==NULL)
		instance = new Player();

	return *instance;	
}

 const TrainList::iterator Player::beginTrainList()
{
	return trainList.begin();
}

 const TrainList::iterator Player::endTrainList()
{
	return trainList.end();
}
 void Player::addTrain(Train * const train)
{
	 trainList.push_back(train);
}


void Player::free()
{
	if(instance!=NULL)
	{
		delete instance;
		instance=NULL;
	}
}

void Player::updateTrains()
{
	for(TrainList::iterator iter = trainList.begin();iter!=trainList.end();iter++)
	{
		if(typeid(*(*iter))==typeid(PassengerTrain))
		{
			dynamic_cast<PassengerTrain*>((*iter))->update();
		}
	}
}

std::ostream & operator<< (std::ostream &w, const Player &p)
{
	return w;//<<p.shipHealth<<" "<<p.playerEnergy<<" "<<p.scor<<" ";
}

std::istream & operator>> (std::istream &w, Player &p)
{
	//w>>p.shipHealth>>p.playerEnergy>>p.scor;
	return w;
}

Player * Player::instance = new Player();
