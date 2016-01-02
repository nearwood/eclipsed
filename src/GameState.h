#pragma once

#include <list>
#include <unordered_map>

#include "json/json.h"

#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "PlayerBoard.h"

class GameState
{
private:
	//std::list<GameState*> children;

public:
	std::list<PlayerBoard*> players;
	std::string currentPlayer, firstPlayer, lastFirstPlayer; //dumb but works for now
	std::list<Sector*> sectors; //some kind of map representation... but not a tree since the core and each player start separate?
	//also, should just keep one large, static list of all sectors and then some state of which ones are placed
	std::list<Tech*> tech; //shown for purchase and remaining?
	//same as sector, one static list of all tech, then each state has status of available ones
	
	short int round;
	
	GameState();
	GameState(GameState& other);
	static GameState* fromJson(Json::Value& races, Json::Value& sectors, Json::Value& initialState);
	static std::list<GameState*> generateChildren(GameState& parent);
	bool isGameOver();
	int getVP(PlayerBoard* p);
	std::unordered_map<std::string, int> getScores();
	PlayerBoard* getFirstPlayer();
	PlayerBoard* getCurrentPlayer();
	PlayerBoard* getNextPlayer();
	PlayerBoard* getLastFirstPlayer();
	bool allPlayersPass();
	//std::list<GameState*> getChildren();
	
	//hashmap of player*->PlayerState?
};
