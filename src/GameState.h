#pragma once

#include <list>
#include <unordered_map>

#include "json/json.h"

#include "map.h"
#include "sector.h"
#include "ship.h"
#include "tech.h"
#include "PlayerBoard.h"

typedef unsigned char byte;

class GameState
{
private:
	//std::list<GameState*> children;

public:
	std::list<PlayerBoard*> players;
	std::string currentPlayer, firstPlayer, lastFirstPlayer; //dumb but works for now
	
	//std::list<Sector*> sectors; //list of all sectors for pulling a random one/copying
	//Sector* gc; //all roads lead to rome
	Map *map;
	
	//also, should just keep one large, static list of all sectors and then some state of which ones are placed
	std::list<Tech*> tech; //shown for purchase and remaining?
	//same as sector, one static list of all tech, then each state has status of available ones
	
	short int round;
	static short int lastRound;
	int depth;
	int numChildren;
	
	GameState();
	~GameState();
	GameState(GameState& other);
	static GameState* fromJson(Json::Value& races, Json::Value& sectors, Json::Value& initialState);
	static std::list<GameState*> generateChildren(GameState& parent);
	bool isGameOver();
	static int getVP(PlayerBoard* p);
	std::unordered_map<std::string, int> getScores();
	PlayerBoard* getPlayer(std::string name);
	PlayerBoard* getFirstPlayer();
	PlayerBoard* getCurrentPlayer();
	PlayerBoard* getNextPlayer();
	PlayerBoard* getLastFirstPlayer();
	void roundCleanup();
	bool allPlayersPass();
	//std::list<GameState*> getChildren();
	
	//hashmap of player*->PlayerState?
};
