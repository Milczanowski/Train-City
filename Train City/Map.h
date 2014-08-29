#pragma once
#include "City.h"
#include <list>
#include <fstream>
#include "MapElement.h"
#include "RailroadTracks.h"

class City;
class MapElement;

typedef std::list<MapElement*> MapElements;
typedef std::list<RailroadTracks> RailroadTracksList;


class Map : public GameObject
{	
private:
	MapElements mapElements;
	RailroadTracksList railroadTrackList;
public:
	Map(const GameObject &, std::string );
	~Map();

	void draw();
	void update();
	void onMouseClickLeft();
	void onMouseClickRight();
	void addRailroadTracks(const RailroadTracks &);
	MapElement * findCity(const std::string)const;
};

inline void Map::addRailroadTracks(const RailroadTracks& railroadTrack)
{
	railroadTrackList.push_back(railroadTrack);
}