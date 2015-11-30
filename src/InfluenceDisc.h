#pragma once

#include "PlayerBoard.h"
#include "sector.h"

//Deprecated... this is too complex
class InfluenceDisc
{
	PlayerBoard* owner;
	Sector* location;
};

typedef InfluenceDisc Disc;
