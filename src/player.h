#pragma once

class Player;

#include "ship.h"

#include <list>
#include <string>

typedef unsigned char sint;

class InfluenceDisc;
typedef InfluenceDisc Disc;

class Player
{
public:
	enum Color {Red, Green, Blue, Yellow, White, Black};
	
	bool pass;
	Color color;
	
	sint e, m, s; //economy, minerals, science
	std::list<Disc*> infAvailable, infSpent;
	
	std::string name;
	
	std::list<Ship*> deployedShips, unbuiltShips;
	
	Player();
};
