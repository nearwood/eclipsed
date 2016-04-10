#pragma once

class SectorLink;

#include "ship.h"
//#include "planet.h"
#include "sectorlink.h"
#include "InfluenceDisc.h"

#include <list>

class Sector
{
public:
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

	SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw;
	Sector *n, *ne, *se, *s, *sw, *nw;

	Sector();
	Sector(Sector& other);
};
