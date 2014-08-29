#pragma once
#include <iostream>
#include <list>
#include "PassengerTrain.h"
#include "Interface.h"

class Train;
class Interface;

typedef std::list<Train *> TrainList;

class Player
{
private:
	TrainList trainList;
	static Player *instance;
	Player(void);
	~Player(void);
public:
	static Player & getInstance();
	static void free();

	void addTrain(Train *);
	TrainList * getTrainList();

	friend std::ostream & operator<< (std::ostream &, const Player &);
	friend std::istream & operator>> (std::istream &, Player &);
};

inline TrainList * Player::getTrainList()
{
	return & trainList;
}

inline void Player::addTrain(Train * train)
{ 
	trainList.push_back(train);
}


inline Player & Player::getInstance()
{
	if(instance==NULL)
		instance = new Player();

	return *instance;	
}

