#pragma once

class SectorLink;

#include "ship.h"
#include "planet.h"
#include "sectorlink.h"
#include "InfluenceDisc.h"

#include <list>

class Sector
{
public:
	std::list<Planet> planets;
	bool ancientSpawn;
	bool ancientBonus; //?
	short int id;

	Disc* influence;
	std::list<Ship*> ships;

	SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw;
	Sector *n, *ne, *se, *s, *sw, *nw;

    Sector();
};
