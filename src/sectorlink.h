#ifndef SECTORLINK_H
#define SECTORLINK_H

class SectorLink;
class Sector;

#include "sector.h"

class SectorLink
{
public:
	//enum LinkType { NONE, HALF, FULL }; //
	//LinkType linkType; //Not needed

	Sector *from, *to;
	//SectorLink *linkedSector; //other side

	SectorLink();
};

#endif // SECTORLINK_H
