#pragma once

#include "sector.h"
#include "sectorlink.h"

#include <list>

class Map
{
	std::list<Sector*> sectors; //ref?
	Sector* gc;
	
public:
	Map();
	Map(Map& other);

	static Sector* NullSector;

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
	
	//Sector* createEmptySector();
	void placeSector(Sector* s);
};

