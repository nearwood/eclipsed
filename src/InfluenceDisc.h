#pragma once

#include "PlayerBoard.h"

class InfluenceDisc
{
	PlayerBoard* owner;
	short int sectorId;
	bool used;
	
public:
	
	
	InfluenceDisc(PlayerBoard* pb, short int sectorId, bool used)
	{
		owner = pb;
		this->sectorId = sectorId;
		this->used = used;
	}

	InfluenceDisc(PlayerBoard* pb, short int sectorId)
	{//ctr called at game setup
		owner = pb;
		this->sectorId = sectorId;
		used = false;
	}
	
	void setSector(short int id)
	{
		sectorId = id;
	}
	
	short int getSector()
	{//what's the point of it being private now...
		return sectorId;
	}
	
	void free() { used = false; } //if (sectorId = 0) used = false; }
	bool isUsed() { return used; }
	void use() { used = true; } //TODO check if already used and throw
	bool isFree() { return sectorId == 0 && !used; }
	bool isPlaced() { return sectorId != 0 && !used; }
};

typedef InfluenceDisc Disc;
