#pragma once

#include "sector.h"
#include "sectorlink.h"

#include <list>

class Map
{
	std::list<Sector*> sectors;
	Sector* gc;
	
public:
	std::list<Sector*> getAllSectors();
	
	Sector* getGalacticCenter() { return this->gc; }
	std::list<Sector*> getRing1Sectors();
	std::list<Sector*> getRing2Sectors();
	std::list<Sector*> getRing3Sectors();
	
	Sector* getRandomRing1Sector();
	Sector* getRandomRing2Sector();
	Sector* getRandomRing3Sector();
};
