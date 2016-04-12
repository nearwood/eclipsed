#pragma once

class SectorLink;

#include "ship.h"
//#include "planet.h"
#include "sectorlink.h"
#include "InfluenceDisc.h"

#include <list>

class Sector
{
	bool isEmpty;
	
public:
	enum Side { N, NE, SE, S, SW, NW };
	
	//std::list<Planet> planets;
	bool ancientSpawn;
	bool ancientBonus; //?
	bool startSector;
	short int id;
	short int ring;
	short int eco, min, sci;
	short int aeco, amin, asci;

	Disc* influence;
	std::list<Ship*> ships;

	SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw; //actual physical rep.
	Sector *n, *ne, *se, *s, *sw, *nw; //internal usage, direct to valid sectors only?

	Sector();
	Sector(Sector& other);
	
	static Sector* createEmptySector(short int ring = 0);
};
