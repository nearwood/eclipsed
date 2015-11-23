#pragma once

#include "player.h"
#include "sector.h"

class InfluenceDisc
{
	Player* owner;
	Sector* location;
};

typedef InfluenceDisc Disc;
