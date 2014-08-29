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
};

