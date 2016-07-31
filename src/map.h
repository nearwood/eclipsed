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
	//need random access for random pick, and always < 50 elements
	std::vector<Sector*> availableSectors, sectors;
	Sector* gc;
	std::vector<Sector*>::const_iterator getAvailableSectorIteratorById(short int id);
	
public:
	Map();
	Map(const Map& other);
	~Map();

	//static Sector* NullSector;

	void setAvailableSectors(std::vector<Sector> sectorList);
	//void setSectors(sectormap s);
	short int size();
	
	std::vector<Sector*> getAllSectors(); //TODO should be ref
	
	Sector* getPlacedSectorById(short int id);
	Sector* getAvailableSectorById(short int id);
	std::vector<Sector*> getPotentialAdjacentSectors(Sector& s);
	
	Sector* getGalacticCenter() { return this->gc; }
	
	//TODO verify any Sector* argument exists in this map, or just use ID
	void setGalacticCenter(Sector* s) { this->gc = s; }
	std::vector<Sector*> getRingSectors(int ring);
	
	Sector* getRandomRingSector(int ring);
	
	void placeSector(short int id);
	
	static int getRing(int q, int r, int s);
	//static Sector* createEmptySector();
	//static void adjacentSectors(Sector* a, Sector* b, Sector::Side s);
};
