#pragma once

#include <list>

#include "GameState.h"
#include "sector.h"
#include "ship.h"
#include "PlayerBoard.h"

class Game
{
	GameState* startState;
	uint depth;
	
public:
	//things available from the game itself, not any single instance
	static std::list<PlayerBoard> players;//TODO not used
	static std::list<Sector*> sectors;
	
	Game(GameState* initialState);
	~Game();
	void play(); //main loop
	std::unordered_map<std::string, int> play(GameState* s, uint depth);
	void turn();
};
