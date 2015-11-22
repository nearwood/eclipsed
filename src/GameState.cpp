
#include "GameState.h"

GameState GameState::fromJson(Json::Value initialState)
{
	
}

bool GameState::isGameOver()
{
	//do some trivial stuff quickly to determine who won
	return false;
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
