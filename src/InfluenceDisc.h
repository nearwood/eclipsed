#pragma once

#include "PlayerBoard.h"
#include "sector.h"

class InfluenceDisc
{
	PlayerBoard* owner;
	Sector* location;
	
public:
	InfluenceDisc(PlayerBoard* pb, Sector* s)
	{
		owner = pb;
		location = s;
	}
	
	void setSector(Sector* s)
	{
		location = s;
	}
	
	bool isFree() { return location == nullptr; }
};

typedef InfluenceDisc Disc;
