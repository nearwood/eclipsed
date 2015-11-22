#pragma once

#include <list>

#include "GameState.h"
#include "sector.h"
#include "ship.h"
#include "player.h"

class Game
{
public:
	std::list<Player*> players;
	std::list<Sector*> sectors;
	
	Game();
	Game(GameState initialState);
	void play(); //main loop
};
