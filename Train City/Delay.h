#pragma once
#include <ctime>
#include "SDL.h"

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
};

inline void Delay::Restart()
{
	startTime = std::clock();
}

inline const bool Delay::isRedy()const
{	
	return (delay <= (unsigned int)(std::clock() - startTime));
}

