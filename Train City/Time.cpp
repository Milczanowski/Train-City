#include "stdafx.h" 
#include "Time.h"


Time::Time() :millisecond(0), second(0), minute(0), hour(0), currentTime(std::clock())
{
	srand((int)time(NULL));
}


Time::~Time()
{
}



float Time::deltaTime = 0;