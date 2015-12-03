
#include "GameState.h"

GameState::GameState()
:round(0)
{
	
}

GameState::GameState(const GameState& other)
:currentPlayer(other.currentPlayer),
firstPlayer(other.firstPlayer),
phase(other.phase),
round(other.round)
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
	return false;
}

int GameState::getVP(PlayerBoard* p)
{
	//assuming p is in list, how many VP does it have?
	return 0;
	/*
	•	Reputation Tiles (1–4 VP per tile)
	•	Ambassador Tiles (1 VP per tile)
	•	Hexes with an Influence Disc (1–4 VP per hex)
	•	Discovery Tiles (2 VP per tile that was kept VP side up)
	•	Monoliths on own hexes (3 VP per Monolith)
	•	Progress on the Technology Tracks:
		4 Technology Tiles on a track = 1 VP,
		5 tiles = 2 VP, 6 tiles = 3 VP, 7 tiles = 5 VP
	•	Traitor Card (–2 VP!)
	•	Species bonuses
	
	two player game
	The two player game is strategically slightly different from
	the multiplayer game. Players should also be advised that
	the Descendants and Planta benefit from their species-spe­
	cific fast expansion capabilities and are thus stronger than
	other species in a two-player setting. It is recommended
	not to use these species in a two player game.
	
	In case of a tie, the total amount of Resources (Money,
	Science and Materials) in each tied player’s Storage is the
	tie breaker.
	*/
}

PlayerBoard* GameState::getFirstPlayer()
{
	return players.size() > 0 ? players.front() : NULL;
}

PlayerBoard* GameState::getCurrentPlayer()
{
	return players.size() > 0 ? players.front() : NULL;
}

std::list<GameState*> GameState::getChildren()
{
	if (children.size() == 0)
		return children = generateChildren();
	else
		return children;
}

std::list<GameState*> GameState::generateChildren()
{
	//build, upgrade, research, explore, move, influence, colonize, diplomacy, pass
	//when everyone passes combat phase
	//combat is random
	PlayerBoard* p = this->currentPlayer; //XXX
	
	
	
	if (p && !p->pass)
	{
		GameState* child = new GameState(*this);
		child->currentPlayer->pass = true;
		children.push_back(child);
		
		//check if first player to pass
		for (PlayerBoard* l : child->players)
		{
			if (l->pass && l != child->currentPlayer)
			{
				firstPlayer = l;
				break;
			}
		}
	}
	else
	{//reactions
		//build, upgrade, move
	}
	
	
	
	//for p1...pN
	//action phase
	//starting with p1
	//allow action (or pass)
	//go to next player
	//repeat until all players pass, first passer is p1 next round
	
	//combat phase
	//upkeep phase
	//cleanup
	
	return children;
}
