#pragma once
#include <ctime>
#include "SDL.h"
#include <iostream>

class Delay
{
private:
	std::clock_t startTime;
	unsigned int delay;
public:
	Delay(const unsigned int);
	~Delay();
	void Restart();
	const bool isRedy()const;

	friend std::ostream & operator<< (std::ostream &, const Delay &);
	friend std::istream & operator>> (std::istream &, Delay &);
};




inline void Delay::Restart()
{
	startTime = std::clock();
}

inline const bool Delay::isRedy()const
{	
	return (delay <= (unsigned int)(std::clock() - startTime));
}

