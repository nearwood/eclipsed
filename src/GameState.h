#pragma once

#include <list>

#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "player.h"

class GameState
{
	enum Phase {};
	std::list<Player*> players;
	std::list<Sector*> sectors;
	std::list<Tech*> tech; //shown for purchase and remaining?
	
	//hashmap of player*->PlayerState?
	//some kind of map representation... but not a tree since the core and each player start separate?
};
