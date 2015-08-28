#ifndef SECTOR_H
#define SECTOR_H

class SectorLink;

#include "ship.h"
#include "planet.h"
#include "sectorlink.h"

#include <QList>

class Sector
{
public:
	QList<Planet> planets;
	bool ancientSpawn;
	bool ancientBonus;
	int id;

	QList<Ship> ships;

	SectorLink *ln, *lne, *lse, *ls, *lsw, *lnw;
	Sector *n, *ne, *se, *s, *sw, *nw;

    Sector();
};

#endif // SECTOR_H
