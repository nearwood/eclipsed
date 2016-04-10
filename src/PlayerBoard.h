#pragma once

class PlayerBoard;

#include "ship.h"
#include "race.h"

#include <list>
#include <string>

typedef unsigned char sint;

class InfluenceDisc;
typedef InfluenceDisc Disc;

/**
 * Might want to keep references to original name, color, to try and keep mem down? Not that big of a deal?
 */
class PlayerBoard //: Race?
{
public:
	Race& race;
	
	sint num; //play order
	bool pass;
	short int colonies;
	
	sint e, m, s; //economy, minerals, science
	sint moves, builds, upgrades; //num builds, upgrades, moves used out of total
	std::list<Disc*> infAvailable, infSpent;
	
	std::string name; //TODO just keep ref to original?
	
	std::list<Ship*> deployedShips, unbuiltShips;
	
	PlayerBoard(Race& r);
	PlayerBoard(PlayerBoard& other);
};
