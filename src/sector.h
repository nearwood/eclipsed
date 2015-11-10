#ifndef SECTOR_H
#define SECTOR_H

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
	bool ancientBonus;
	int id;

	std::list<Disc*> discs;
	std::list<Ship*> ships;

	SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw;
	Sector *n, *ne, *se, *s, *sw, *nw;

    Sector();
};

#endif // SECTOR_H
