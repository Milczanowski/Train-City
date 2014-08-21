#include "stdafx.h" 
#include "Delay.h"


Delay::Delay(const unsigned int delay) :delay(delay), startTime(std::clock())
{
}


Delay::~Delay()
{
}
