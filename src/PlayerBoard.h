#pragma once

class PlayerBoard;

#include "ship.h"
#include "race.h"
#include "map.h"

#include <vector>
#include <string>
#include <map>

typedef unsigned char byte;

//30 25 21 17 13 10 7 5 3 2 1 0 0

//1  2  3  4  5  6  7   8   9   10  11  12
//0, 1, 2, 3, 5, 7, 10, 13, 17, 21, 25, 30
//0,    1,    2,   3,   5,   7,   10,  13,  17,  21,  25,  30
//2n-2, 2n-3, 2n-4 2n-5 2n-5 2n-5 2n-4 2n-3 2n-1 2n+1 2n+3 2n+6
//ugh just use a map...

class Map;
class InfluenceDisc;
typedef InfluenceDisc Disc;

/**
 * Might want to keep references to original name, color, to try and keep mem down? Not that big of a deal?
 */
class PlayerBoard //: Race?
{
	std::vector<Disc*> inf; //TODO list of actioned/sectored vs free
	static std::map<byte, byte> actionCost;
	bool dead;
	
public:
	Race& race; //TODO should be const, no easy way
	byte num; //play order
	bool pass;
	short int colonyShips, usedColonyShips;
	
	char e, m, s; //economy, minerals, science
	byte moves, builds, upgrades; //num builds, upgrades, moves used out of total
	
	std::string name; //TODO just keep ref to original?
	
	std::vector<Ship*> deployedShips, unbuiltShips;
	
	PlayerBoard(Race& r);
	PlayerBoard(PlayerBoard& other);
	~PlayerBoard();
	
	short int getRemainingActions();
	Disc* getFreeInfluence();
	std::vector<Disc*> getPlacedInfluence();
	void placeInfluence(Sector* s);
	void razeSector(Sector *s);
	void razeSector(Disc *d);
	void removeFromGame();
	bool isActive();
	byte getActionCost();
	
	void roundCleanup();
	
	short int getVP(Map* map);
};
