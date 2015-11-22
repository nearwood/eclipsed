#pragma once

#include <list>

#include "json/json.h"

#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "player.h"

class GameState
{
public:
	short int round;
	enum Phase {};
	std::list<Player*> players;
	std::list<Sector*> sectors; //some kind of map representation... but not a tree since the core and each player start separate?
	std::list<Tech*> tech; //shown for purchase and remaining?
	std::list<GameState*> children;
	
public:
	static GameState fromJson(Json::Value initialState);
	bool isGameOver();
	int getVP(Player* p);
	Player* getFirstPlayer();
	Player* getCurrentPlayer();
	std::list<GameState*> getChildren();
	
	//hashmap of player*->PlayerState?
};
