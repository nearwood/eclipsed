#ifndef SECTOR_H
#define SECTOR_H

#include <QList>

#include "planet.h"
#include "sectorlink.h"

class Sector
{
public:
	QList<Planet> planets;
	bool ancientSpawn;
	bool ancientBonus;
	int id;

	QList<Ship> ships;

	SectorLink *n, *ne, *se, *s, *sw, *nw;
	Sector *n, *ne, *se, *s, *sw, *nw;

    Sector();
};

#endif // SECTOR_H
