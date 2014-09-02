#include "StdAfx.h"
#include "Train.h"


Train::Train(const float averageSpeed,const unsigned int capacity, MapElement * const target)
	:averageSpeed( fabs(averageSpeed)), capacity(capacity), target(target), delay(Delay(0)),
	currentBurden(0),direction(Vector2(0,0)),positon(Vector2(0,0)),distance(0)
{
	if(target!=NULL)
		positon= target->getCenterPosition();
}

Train::~Train(void)
{
}

MapElement * const Train::getTarget()const
{
	return this->target;
}

Product * const Train::getProduct(const std::string name)
{
	if(typeid(*target)==typeid(City))
	{
		return &(*dynamic_cast<City*>(target)->getProduct(name));
	}else throw GameError("Wrong target");

}

void Train::draw()
{
	if(!delay.isRedy())
	{
		positon-= direction * (Time::getDetlaTime()/(distance/averageSpeed));
		SDL_Rect rect = {(int)positon.get_X()-3 ,(int)positon.get_Y()-3,6,6};
		SDL_RenderFillRect(GraphicDevice::getRenderer(), &rect);
	}
}

void Train::goTo(MapElement * const target)
{
	if(target!=NULL)
	{
		direction = Vector2(this->target->getCenterPosition().get_X()- target->getCenterPosition().get_X()
			,this->target->getCenterPosition().get_Y()- target->getCenterPosition().get_Y());
		distance = target->getCenterPosition().distance(this->target->getCenterPosition());
		Player::getInstance().removeCash((int)distance/20);

		this->target= target;
		delay = Delay((int)((int)distance/averageSpeed));
		delay.Restart();
	}
}


const bool Train::isReady()const
{
	return delay.isRedy();
}