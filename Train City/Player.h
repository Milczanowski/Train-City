#pragma once
#include <iostream>
#include <list>
#include "Interface.h"
#include "PassengerTrain.h"


class Train;
class Interface;
class MapElement;

typedef std::list<Train *> TrainList;

class Player
{
private:
	int cash;
	TrainList trainList;
	static Player *instance;
	Player(void);
	~Player(void);
public:
	static Player & getInstance();
	static void free();
	void addCash(const unsigned int);
	void removeCash(const unsigned int);
	void addTrain(Train * const);
	const TrainList::iterator beginTrainList();
	const TrainList::iterator endTrainList();
	const TrainList getTrainList()const;
	void updateTrains();
	void drawTrains()const;
	void drawCash(const Vector2 &, const float textSize)const;

	friend std::ostream & operator<< (std::ostream &, const Player &);
	friend std::istream & operator>> (std::istream &, Player &);
};

