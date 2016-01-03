
#include "GameState.h"

#include <iostream>

using namespace std;

GameState::GameState()
:round(0)
{
	
}

GameState::GameState(GameState& other)
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

GameState::~GameState()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		delete *it;
		
	//TODO sectors
}

GameState* GameState::fromJson(Json::Value& races, Json::Value& sectors, Json::Value& initialState)
{
	GameState* s = new GameState();
	
	s->round = 1;
	
	//load all races
	//load game json, players, and assign playerboards with race
	//delete unused races
	std::list<Race*> racesList; //might want a hashmap for easy deletion later
	const Json::Value racesJson = races["races"];
	for (uint i = 0; i < racesJson.size(); ++i)
	{
		Json::Value jr = racesJson[i];
		Race *r = new Race();
		r->color = Race::Color::Red; //y do i care?
		Json::Value storage = jr["storage"];
		//assert storage.size() == 3
		r->e = storage[0].asInt();
		r->m = storage[1].asInt();
		r->s = storage[2].asInt();
		r->name = jr.get("name", "UNKNOWN").asString();
		racesList.push_back(r);
	}
	
	const Json::Value players = initialState["players"];
	for (uint i = 0; i < players.size(); ++i)
	{
		Json::Value po = players[i];
		Race *race = nullptr;
		//get the name of this player, find the race with that name and use that race as the base.
		std::string name = po.get("name", "UNKNOWN").asString();
		for (auto it = racesList.cbegin(); it != racesList.cend(); ++it)
		{
			if ((*it)->name == name)
			{
				race = *it;
				break;
			}
		}
		
		if (!race)
		{
			//cerr << "Could not find race: " << name << endl;
			continue;
		}
		
		PlayerBoard *pb = new PlayerBoard(*race);
		pb->name = race->name;
		pb->num = po.get("player", i + 1).asInt();
		s->players.push_back(pb);
		
		int playerNum = po.get("player", 0).asInt();
		if (playerNum == 1 || i == 0)
		{
			s->firstPlayer = pb->name;
			s->lastFirstPlayer = pb->name;
			s->currentPlayer = pb->name;
		}
	}
	
	//This seems horridly inefficient...
	std::list<Race*> deleteList;
	for (auto rit = racesList.cbegin(); rit != racesList.cend(); ++rit)
	{
		bool deleteMe = true;
		for (auto pit = s->players.cbegin(); pit != s->players.cend(); ++pit)
		{
			if (&(*pit)->race == (*rit))
			{
				deleteMe = false;
				break;
			}
		}
		
		if (deleteMe) deleteList.push_back(*rit);
	}
	
	while (!deleteList.empty())
	{
		cout << "Freeing unused race: " << deleteList.front()->name << endl;
		delete deleteList.front();
		deleteList.pop_front();
	}
	
	return s;
}

//do some trivial stuff quickly to determine who won
bool GameState::isGameOver()
{
	if (round == 3) return true;
	
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

/**
 * Get a list of resulting board states that constitute all possibilities for a player.
 */
std::list<GameState*> GameState::generateChildren(GameState& parent)
{
	//build, upgrade, research, explore, move, influence, colonize, diplomacy, pass
	//when everyone passes combat phase
	//combat is random
	
	std::list<GameState*> children;
	GameState* childState = new GameState(parent);
	
	PlayerBoard *currentBoard = childState->getCurrentPlayer();
	cout << "Playing as: " << currentBoard->name << endl;
	//TODO assert currentBoard != nullptr
	if (!currentBoard->pass)
	{//try passing if we haven't already
		cout << "Pass" << endl;
		currentBoard->pass = true;
		
		//check if first pass
		bool firstPass = true;
		for (PlayerBoard* l : childState->players)
		{
			if (l->pass && l != currentBoard)
			{
				firstPass = false;
				break;
			}
			
			//TODO Do last pass check here
		}
		
		if (firstPass)
		{//If first pass set next round's first player.
			childState->lastFirstPlayer = childState->firstPlayer;
			childState->firstPlayer = currentBoard->name;
		}
		
		//going to have to force a pass at some point, preferably soon after e < 0 as you cannot action all your owned space away, and there are diminishing returns up to that point.
		
		PlayerBoard *nextPlayer = childState->getNextPlayer();
		childState->currentPlayer = nextPlayer->name; //TODO Null check?
		
		children.push_back(childState);
	}
	else
	{
		if (childState->allPlayersPass())
		{//If last pass, end the round
			cout << "All players pass" << endl;
			//TODO Do all phases here.
			
			//go to next round if there is one
			childState->round++;
			for (PlayerBoard* l : childState->players)
			{
				l->pass = false;
				//do whatever else resets here.
				//COMBAT do all potential combat from all potential actions (using averages?) (starting from sectors numbers IIRC)
				//UPKEEP e,m,s balancing
				//CLEANUP //prob. redundant.
			}
			
			children.push_back(childState);
		}
		else
		{
			delete childState;
			//reactions
			//build, upgrade, move
		}
	}
	
	cout << "Generated " << children.size() << " children." << endl;
	return children;
}
