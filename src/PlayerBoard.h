#pragma once

class PlayerBoard;

#include "ship.h"

#include <list>
#include <string>

typedef unsigned char sint;

class InfluenceDisc;
typedef InfluenceDisc Disc;

/**
 * Might want to keep references to original name, color, to try and keep mem down? Not that big of a deal?
 */
class PlayerBoard
{
public:
	enum Color {Red, Green, Blue, Yellow, White, Black};
	
	sint num; //play order
	bool pass;
	short int colonies;
	Color color; //TODO just keep ref to original?
	
	sint e, m, s; //economy, minerals, science
	std::list<Disc*> infAvailable, infSpent;
	
	std::string name; //TODO just keep ref to original?
	
	std::list<Ship*> deployedShips, unbuiltShips;
	
	PlayerBoard();
	PlayerBoard(const PlayerBoard& other);
};
