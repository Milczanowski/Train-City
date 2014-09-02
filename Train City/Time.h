#pragma once
#include <time.h>
#include <ctime>
#include "Vector2.h"
#include "GraphicDevice.h"
class Time
{
private:
	std::clock_t currentTime;
	float millisecond;
	static float deltaTime;
	unsigned int second, minute, hour;
	const bool addTime(unsigned int *, const unsigned int);
	
public:
	Time();
	~Time();
	void update();
	void draw(const SDL_Color, const Vector2 &, const float )const;
	static const float getDetlaTime();

	friend std::ostream & operator<< (std::ostream &, const Time &);
	friend std::istream & operator>> (std::istream &, Time &);
};




inline void Time::draw(const SDL_Color color, const Vector2 & position, const float size)const
{
	GraphicDevice::drawText(ToString<int>(hour) + " : " + ToString<int>(minute) + " : " + ToString<int>(second), color, position, size);
}

inline const float Time::getDetlaTime()
{
	return deltaTime;
}

inline void Time::update()
{
	std::clock_t   start = std::clock();	
	deltaTime = float(start - currentTime) / (float)(CLOCKS_PER_SEC / 1000);
	currentTime = start;
	millisecond += deltaTime;

	if (millisecond >= 1000)
	{
		millisecond -= 1000;
		if (addTime(&second, 59))
			if (addTime(&minute, 60))
				addTime(&hour, 24); 
	}
}

inline const bool Time::addTime(unsigned int * value, const unsigned int limit)
{
	*(value) += 1; 
	if (*value >= limit)
	{
		*value %= limit;
		return true;
	}
	else
		return false;
}

