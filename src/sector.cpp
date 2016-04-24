#include "sector.h"

#include <cmath>

Sector* NullSector = new Sector(0, 0, 0);

Sector::Sector(short int q, short int r, short int s):
d(-1),
ring(-1),
id(-1),
vp(-1),
eco(-1),
min(-1),
sci(-1),
aeco(-1),
amin(-1),
asci(-1),
influence(nullptr)
{
	this->q = q;
	this->r = r;
	this->s = s;
}

Sector::Sector(const Sector& other):
d(other.d),
//planets(other.planets),
ancientSpawn(other.ancientSpawn),
ancientBonus(other.ancientBonus),
startSector(other.startSector),
ring(other.ring),
id(other.id),
q(other.q),
r(other.r),
s(other.s),
vp(other.vp),
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
