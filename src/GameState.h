#pragma once

#include <list>

#include "json/json.h"

#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "PlayerBoard.h"

class GameState
{
private:
	std::list<GameState*> children;
	std::list<GameState*> generateChildren();

public:
	std::list<PlayerBoard*> players;
	PlayerBoard *currentPlayer, *firstPlayer;
	std::list<Sector*> sectors; //some kind of map representation... but not a tree since the core and each player start separate?
	//also, should just keep one large, static list of all sectors and then some state of which ones are placed
	std::list<Tech*> tech; //shown for purchase and remaining?
	//same as sector, one static list of all tech, then each state has status of available ones
	
	enum Phase {Action, Combat, Upkeep, Cleanup} phase;
	short int round;
	
	GameState();
	GameState(const GameState& other);
	static GameState fromJson(Json::Value initialState);
	bool isGameOver();
	int getVP(PlayerBoard* p);
	PlayerBoard* getFirstPlayer();
	PlayerBoard* getCurrentPlayer();
	std::list<GameState*> getChildren();
	
	//hashmap of player*->PlayerState?
};
