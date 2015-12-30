
#include "GameState.h"

GameState::GameState()
:round(0)
{
	
}

GameState::GameState(const GameState& other)
:currentPlayer(other.currentPlayer),
firstPlayer(other.firstPlayer),
lastFirstPlayer(other.lastFirstPlayer),
round(other.round)
{
	for (auto it = other.players.cbegin(); it != other.players.cend(); ++it)
		players.push_back(new PlayerBoard(**it));
	
	//sectors = other.sectors;
	tech = other.tech;
	//children remains empty
}

GameState GameState::fromJson(Json::Value initialState)
{
	GameState s;
	
	s.round = 1;
	
	const Json::Value players = initialState["players"];
	for (uint i = 0; i < players.size(); ++i)
	{
		Json::Value po = players[i];
		PlayerBoard *pb = new PlayerBoard();
		pb->colonies = 0;
		pb->color = PlayerBoard::Color::Red;
		pb->e = 10;
		pb->m = 10;
		pb->s = 10;
		pb->name = po.get("name", "UNKNOWN").asString();
		pb->num = po.get("player", i + 1).asInt();
		s.players.push_front(pb);
		
		int playerNum = po.get("player", 0).asInt();
		if (playerNum == 1 || i == 0)
		{
			s.firstPlayer = pb->name;
			s.lastFirstPlayer = pb->name;
			s.currentPlayer = pb->name;
		}
	}
	
	return s;
}

//do some trivial stuff quickly to determine who won
bool GameState::isGameOver()
{
	if (round == 10) return true;
	
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

std::unordered_map<std::string, int> GameState::getScores()
{
	std::unordered_map<std::string, int> scores;
	
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		scores.insert({ (*it)->name, getVP(*it) });
	
	return scores;
}

PlayerBoard* GameState::getFirstPlayer()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		if ((*it)->name == firstPlayer) return *it;
	
	return nullptr;
}

PlayerBoard* GameState::getCurrentPlayer()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		if ((*it)->name == currentPlayer) return *it;
	
	return nullptr;
}

PlayerBoard* GameState::getLastFirstPlayer()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		if ((*it)->name == lastFirstPlayer) return *it;
	
	return nullptr;
}

PlayerBoard* GameState::getNextPlayer()
{
	//get the player to our "left"
	PlayerBoard* p = getCurrentPlayer();
	
	if (p)
	{
		sint nextNum = p->num + 1;
		if (nextNum > players.size())
			nextNum = 1;
		
		for (auto it = players.cbegin(); it != players.cend(); ++it)
		{
			if (nextNum == (*it)->num)
			{
				return *it;
			}
		}
	}
	
	return nullptr; //invalid input
}

//Check to see if all players have passed.
bool GameState::allPlayersPass()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		if (!(*it)->pass) return false;
	
	return true;
}

std::list<GameState*> GameState::getChildren()
{
	if (children.size() == 0)
		return children = generateChildren();
	else
		return children;
}

/**
 * Get a list of resulting board states that constitute all possibilities for a player.
 */
std::list<GameState*> GameState::generateChildren()
{
	//build, upgrade, research, explore, move, influence, colonize, diplomacy, pass
	//when everyone passes combat phase
	//combat is random
	GameState* childState = new GameState(*this);
	
	PlayerBoard *childBoard = childState->getCurrentPlayer();
	if (childBoard && !childBoard->pass)
	{//try passing if we haven't already
		
		childBoard->pass = true;
		
		//check if first pass
		bool firstPass = true;
		for (PlayerBoard* l : childState->players)
		{
			if (l->pass && l != childBoard)
			{
				firstPass = false;
				break;
			}
			
			//TODO Do last pass check here
		}
		
		if (firstPass)
		{//If first pass set next round's first player.
			childState->lastFirstPlayer = childState->firstPlayer;
			childState->firstPlayer = childBoard->name;
		}
		else if (allPlayersPass())
		{//If last pass, end the round
			//childState->phase = GameState::Phase::Combat;
			//TODO Do all phases here.
			///All the below need to happen at once, combined into one state? (ie, 2 phases: Action or CombatUpkeepCleanup)
			//COMBAT do all potential combat from all potential actions (using averages?)
			//UPKEEP e,m,s balancing
			//CLEANUP //prob. redundant.
			childState->round++;
		}
		
		//going to have to force a pass at some point, preferably soon after e < 0 as you cannot action all your owned space away, and there are diminishing returns up to that point.
		
		PlayerBoard *nextPlayer = getNextPlayer();
		childState->currentPlayer = nextPlayer->name; //TODO Null check?
		
		children.push_back(childState);
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
	
	return children;
}
