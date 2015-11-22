#pragma once

#include <list>

#include "GameState.h"
#include "sector.h"
#include "ship.h"
#include "player.h"

class Game
{
	GameState startState;
	uint depth;
	
public:
	std::list<Player*> players;
	std::list<Sector*> sectors;
	
	Game(GameState initialState);
	void play(); //main loop
	int play(GameState* s, uint depth, Player* p);
	void turn();
};
