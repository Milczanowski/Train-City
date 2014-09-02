#include "StdAfx.h"
#include "RailroadTracks.h"


RailroadTracks::RailroadTracks(const Vector2& start, const Vector2& end):start(start), end(end)
{
}


RailroadTracks::~RailroadTracks(void)
{
}


void RailroadTracks::draw()const
{
	SDL_RenderDrawLine(GraphicDevice::getRenderer(), (int)start.get_X(), (int)start.get_Y(), (int)end.get_X(), (int)end.get_Y());
}


std::ostream & operator<< (std::ostream & v, const RailroadTracks & rT)
{
	return	v<<rT.start<<" "<<rT.end<<std::endl;
}

std::istream & operator>> (std::istream & v, RailroadTracks & rT)
{
	return v>>rT.start>>rT.end;
}
