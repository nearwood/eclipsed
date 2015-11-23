
#include "GameState.h"

GameState::GameState()
:round(0)
{
	
}

GameState::GameState(const GameState& other)
:round(other.round)
{
	players = other.players;
	sectors = other.sectors;
	tech = other.tech;
	//children remains empty
}

GameState GameState::fromJson(Json::Value initialState)
{
	GameState s;
	return s;
}

bool GameState::isGameOver()
{
	//do some trivial stuff quickly to determine who won
	return true;
}

int GameState::getVP(Player* p)
{
	//assuming p is in list, how many VP does it have?
	return 0;
}

Player* GameState::getFirstPlayer()
{
	return players.size() > 0 ? players.front() : NULL;
}

Player* GameState::getCurrentPlayer()
{
	return players.size() > 0 ? players.front() : NULL;
}

std::list<GameState*> GameState::getChildren()
{
	return children;
}
