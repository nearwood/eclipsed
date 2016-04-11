#include "map.h"

Map::Map()
{//eh, is this only for the null sector?
	//sectors = std::list<Sector*>();
	
	//Fill graph
	
	
}

Map::Map(Map& other)
{
	Map();
	//for (auto it = other.sectors.begin(); it != other.sectors.cend(); ++it)
	//	sectors.push_back(new Sector(**it));
	sectors = other.sectors;
	
	gc = other.gc;
	
	//Fill out graph
}

void Map::setSectors(std::list<Sector*> s)
{
	sectors = s; //TODO sort or someshit
}

short int Map::size()
{
	return sectors.size(); //ideally this should be the filled graph size, not just what was loaded.
}

void Map::placeSector(Sector* s)
{
	//uhhhh need null sectors
}

std::list<Sector*> Map::getAllSectors()
{
	return this->sectors;
}

Sector* Map::getSectorById(short int id)
{
	for (auto it = sectors.cbegin(); it != sectors.cend(); ++it)
		if ((*it)->id == id) return (*it);
		
	return nullptr;
}

//Sector* Map::getGalacticCenter() { return this->gc; }
std::list<Sector*> Map::getRing1Sectors()
{
	return std::list<Sector*>();
}

std::list<Sector*> Map::getRing2Sectors()
{
	return std::list<Sector*>();
}

std::list<Sector*> Map::getRing3Sectors()
{
	return std::list<Sector*>();
}

Sector* Map::getRandomRing1Sector()
{
	return nullptr;
}

Sector* Map::getRandomRing2Sector()
{
	return nullptr;
}

Sector* Map::getRandomRing3Sector()
{
	return nullptr;
}
