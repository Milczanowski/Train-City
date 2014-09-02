#include "stdafx.h" 
#include "Time.h"


Time::Time() :millisecond(0), second(0), minute(0), hour(0), currentTime(std::clock())
{
	srand((int)time(NULL));
}


Time::~Time()
{
}

std::ostream & operator<<(std::ostream & w, const Time & time)
{
	return w<<time.hour<<" "<<time.minute<<" "<<time.second<<" "<<time.millisecond<<std::endl;
}

std::istream & operator>> (std::istream & w, Time & time)
{
	return w>>time.hour>>time.minute>>time.second>>time.millisecond;
}




float Time::deltaTime = 0;