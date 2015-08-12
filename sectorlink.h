#ifndef SECTORLINK_H
#define SECTORLINK_H

#include "sector.h"

class SectorLink
{
public:
	enum LinkType { NONE, HALF, FULL }; //Perhaps we should denote direction for halves
	LinkType linkType;

	Sector *sector;
	SectorLink *linkedSector; //other side

	SectorLink();
};

#endif // SECTORLINK_H
