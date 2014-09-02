#include "stdafx.h" 
#include "Delay.h"


Delay::Delay(const unsigned int delay) :delay(delay), startTime(std::clock())
{
}


Delay::~Delay()
{
}


std::ostream & operator<< (std::ostream & v, const Delay &d)
{
	return v<<d.delay<<" "<<d.startTime<<std::endl;
}
std::istream & operator>> (std::istream & v, Delay & d)
{
	return v>>d.delay>>d.startTime;
}