#pragma once
#include "GraphicDevice.h"
#include <SDL.h>


class RailroadTracks
{
private:
	Vector2 start, end;
public:
	RailroadTracks(const Vector2&, const Vector2&);
	~RailroadTracks(void);

	void draw()const;

	friend std::ostream & operator<< (std::ostream &, const RailroadTracks &);
	friend std::istream & operator>> (std::istream &, RailroadTracks &);
};

