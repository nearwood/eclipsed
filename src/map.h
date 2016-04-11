#pragma once

#include "sector.h"
#include "sectorlink.h"

#include <list>

class Map
{
	std::list<Sector*> sectors; //ref?
	Sector* gc;
	
	static const Sector* NullSector;
	
public:
	Map();
	Map(Map& other);

	void setSectors(std::list<Sector*> s);
	short int size();

	std::list<Sector*> getAllSectors(); //TODO should be ref
	Sector* getSectorById(short int id);
	
	Sector* getGalacticCenter() { return this->gc; }
	std::list<Sector*> getRing1Sectors();
	std::list<Sector*> getRing2Sectors();
	std::list<Sector*> getRing3Sectors();
	
	Sector* getRandomRing1Sector();
	Sector* getRandomRing2Sector();
	Sector* getRandomRing3Sector();
	
	void placeSector(Sector* s);
};

static const Sector* NullSector = new Sector();
