#pragma once
#include "City.h"
#include <list>
#include <fstream>
#include "MapElement.h"
#include "RailroadTracks.h"
#include "Schedule.h"

class City;
class MapElement;
class Schedule;

typedef std::list<MapElement*> MapElements;
typedef std::list<RailroadTracks> RailroadTracksList;

class Map : public GameObject
{	
private:
	MapElements mapElements;
	RailroadTracksList railroadTrackList;
	Schedule * schedule;
public:
	Map(const GameObject &, std::string );
	virtual ~Map();

	void draw()const;
	void update();
	void onMouseClickLeft();
	void onMouseClickRight();
	void addRailroadTracks(const RailroadTracks &);
	MapElement * findCity(const std::string)const;
	Schedule * const getSchedule()const;

	friend std::ostream & operator<< (std::ostream &, const Map &);
	friend std::istream & operator>> (std::istream &, Map &);
};


inline void Map::addRailroadTracks(const RailroadTracks& railroadTrack)
{
	railroadTrackList.push_back(railroadTrack);
}