#pragma once

#include <list>

#include "json/json.h"

#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "player.h"

class GameState
{
private:
	std::list<GameState*> children;
	std::list<GameState*> generateChildren();

public:
	std::list<Player*> players;
	Player* currentPlayer; //const?
	std::list<Sector*> sectors; //some kind of map representation... but not a tree since the core and each player start separate?
	std::list<Tech*> tech; //shown for purchase and remaining?
	
	enum Phase {Action, Combat, Upkeep, Cleanup} phase;
	short int round;
	bool pass;
	
	GameState();
	GameState(const GameState& other);
	static GameState fromJson(Json::Value initialState);
	bool isGameOver();
	int getVP(Player* p);
	Player* getFirstPlayer();
	Player* getCurrentPlayer();
	std::list<GameState*> getChildren();
	
	//hashmap of player*->PlayerState?
};
