#pragma once

#include "sector.h"
#include "sectorlink.h"

#include <list>
#include <vector>
//#include <unordered_map>

//typedef std::unordered_map<int, Sector*> sectormap;

class Map
{
	//sectormap sectors; //ref?
	std::list<Sector*> availableSectors, sectors;
	Sector* gc;
	
public:
	Map();
	Map(Map& other);

	//static Sector* NullSector;

	void setAvailableSectors(std::list<Sector*> s);
	//void setSectors(sectormap s);
	short int size();

	std::list<Sector*> getAllSectors(); //TODO should be ref
	Sector* getAvailableSectorById(short int id);
	std::list<Sector*> getPotentialAdjacentSectors(Sector& s);
	
	Sector* getGalacticCenter() { return this->gc; }
	std::list<Sector*> getRing1Sectors();
	std::list<Sector*> getRing2Sectors();
	std::list<Sector*> getRing3Sectors();
	
	Sector* getRandomRing1Sector();
	Sector* getRandomRing2Sector();
	Sector* getRandomRing3Sector();
	
	void placeSector(Sector* s);
	
	static Sector* createEmptySector();
	static void adjacentSectors(Sector* a, Sector* b, Sector::Side s);
};
