#include "map.h"

std::list<Sector*> Map::getAllSectors()
{
	return this->sectors;
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
