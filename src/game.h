#pragma once

#include <list>

#include "GameState.h"
#include "sector.h"
#include "ship.h"
#include "PlayerBoard.h"

class Game
{
	GameState startState;
	uint depth;
	
public:
	//things available from the game itself, not any single instance
	static std::list<PlayerBoard> players;
	static std::list<Sector*> sectors;
	
	Game(GameState initialState);
	void play(); //main loop
	int play(GameState* s, uint depth, PlayerBoard* p);
	void turn();
};
