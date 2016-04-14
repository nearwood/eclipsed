#include "sector.h"

#include <cmath>

Sector::Sector():
isEmpty(false),
d(-1),
ring(-1),
id(-1),
eco(-1),
min(-1),
sci(-1),
aeco(-1),
amin(-1),
asci(-1),
influence(nullptr)
{
	for (int i = 0; i < 6; ++i)
	{
		//nbr[i] = link[i] = nullptr;
	}
}

Sector::Sector(Sector& other):
d(-1),
//planets(other.planets),
ancientSpawn(other.ancientSpawn),
ancientBonus(other.ancientBonus),
startSector(other.startSector),
ring(-1),
id(other.id),
eco(other.eco),
min(other.min),
sci(other.sci),
aeco(other.aeco),
amin(other.amin),
asci(other.asci),
influence(other.influence),
ships(other.ships)
{
	for (int i = 0; i < 6; ++i)
	{
		//nbr[i] = other.nbr[i];
		link[i] = other.link[i];
	}
}

short int Sector::getDistance(Sector* from) //TODO imp arg
{
	return d >= 0 ? d : d = std::max(std::max(abs(q), abs(r)), abs(s));
}

Sector* Sector::createEmptySector(short int ring)
{
	Sector* s = new Sector();
	s->isEmpty = true;
	s->ring = ring;
	
	//TODO visit all non-null neighbors in ring and link
	
	return s;
}
