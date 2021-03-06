#pragma once

class SectorLink;

#include "ship.h"
//#include "planet.h"
#include "sectorlink.h"
#include "InfluenceDisc.h"

#include <list>

class spos
{
	short int q, r, s;
	
	//TODO operator=, distance etc.
};

class Sector
{
	short int d;
	
public:
	static Sector* NullSector;

	enum Side { N, NE, SE, S, SW, NW };
	
	//std::list<Planet> planets;
	bool ancientSpawn;
	bool ancientBonus; //?
	bool startSector;
	short int ring; //game ring, 0, 1, 2, 3 (for 3+)
	short int id;
	short int q, r, s;
	short int vp;
	short int eco, min, sci;
	short int aeco, amin, asci;

	Disc* influence;
	std::list<Ship*> ships;

	//movement along edges only, no vertices needed
	//SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw; //actual physical rep.
	//Sector *n, *ne, *se, *s, *sw, *nw; //internal usage, direct to valid sectors only?
	//Sector* nbr[6]; //neighbor
	Sector* link[6];

	Sector(short int q, short int r, short int s);
	Sector(const Sector& other);
	
	//static Sector* createEmptySector(short int ring = 0);
	short int getDistance(Sector* from = nullptr);
};
