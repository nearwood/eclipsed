
#include "GameState.h"

#include <iostream>
#include <vector>

using namespace std;

GameState::GameState()
:round(0)
{
	map = new Map();
}

GameState::GameState(GameState& other)
:currentPlayer(other.currentPlayer),
firstPlayer(other.firstPlayer),
lastFirstPlayer(other.lastFirstPlayer),
map(other.map),
round(other.round)
{
	for (auto it = other.players.cbegin(); it != other.players.cend(); ++it)
		players.push_back(new PlayerBoard(**it));
	
	tech = other.tech;
	
	//children remains empty
}

GameState::~GameState()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		delete *it;
		
	//TODO sectors
}

//Initial state... TODO any state (!)
GameState* GameState::fromJson(Json::Value& races, Json::Value& sectors, Json::Value& initialState)
{
	GameState* gs = new GameState();
	
	gs->round = 1;
	
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
	cout << "Loaded " << racesList.size() << " races. " << sizeof(Race) * racesList.size() + sizeof(racesList) << " bytes." << endl;
	
	std::list<Sector*> sectorList;
	const Json::Value sectorsJson = sectors["sectors"];
	for (uint i = 0; i < sectorsJson.size(); ++i)
	{
		Json::Value js = sectorsJson[i];
		Sector *s = new Sector(-1, -1, -1);
		s->ring = js["ring"].asInt();
		s->id = js["id"].asInt();
		s->ancientSpawn = js["ancient"].asBool();
		s->startSector = js["startSector"].asBool();
		
		Json::Value squares = js["squares"];
		//assert storage.size() == 3
		s->eco = squares[0].asInt();
		s->min = squares[1].asInt();
		s->sci = squares[2].asInt();
		
		Json::Value advSquares = js["advancedSquares"];
		//assert storage.size() == 3
		s->aeco = advSquares[0].asInt();
		s->amin = advSquares[1].asInt();
		s->asci = advSquares[2].asInt();
		
		//s->name = js.get("name", "UNKNOWN").asString();
		sectorList.push_back(s);
	}
	gs->map->setAvailableSectors(sectorList);
	cout << "Loaded " << sectorList.size() << " sectors. " << sizeof(Sector) * sectorList.size() + sizeof(sectorList) << " bytes." << endl;
	
	//Get Galactic Center
	Sector* sector = gs->map->getAvailableSectorById(1);
	sector->q = 0;
	sector->r = 0;
	sector->s = 0;
	gs->map->placeSector(sector);
	//sector-> //TODO Setup GC defense, etc.
	
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
			//cerr << "404 race not found: " << name << endl;
			continue;
		}
		
		PlayerBoard *pb = new PlayerBoard(*race);
		pb->num = po.get("player", i + 1).asInt();
		gs->players.push_back(pb);
		
		//setup first player
		int playerNum = po.get("player", 0).asInt();
		if (playerNum == 1 || i == 0)
		{
			gs->firstPlayer = pb->name;
			gs->lastFirstPlayer = pb->name;
			gs->currentPlayer = pb->name;
		}
		
		//setup starting sector
		int startSector = po.get("startSector", 9000).asInt();
		Sector* sector = gs->map->getAvailableSectorById(startSector);
		sector->startSector = true;
		switch (i)
		{//TODO Fix this
			case 0:
			sector->q = 2;
			sector->r = 0;
			sector->s = 0;
			break;
			case 1:
			sector->q = 0;
			sector->r = 2;
			sector->s = 0;
			break;
			case 2:
			sector->q = 0;
			sector->r = 0;
			sector->s = 2;
			break;
		}
		gs->map->placeSector(sector);
		pb->placeInfluence(sector);
	}
	
	//This seems horridly inefficient...
	std::list<Race*> deleteList;
	for (auto rit = racesList.cbegin(); rit != racesList.cend(); ++rit)
	{
		bool deleteMe = true;
		for (auto pit = gs->players.cbegin(); pit != gs->players.cend(); ++pit)
		{
			if (&(*pit)->race == (*rit))
			{
				deleteMe = false;
				break;
			}
		}
		
		if (deleteMe) deleteList.push_back(*rit);
	}
	
	short int r = 0;
	while (!deleteList.empty())
	{
		r++;
		cout << "Freeing unused race: " << deleteList.front()->name << endl;
		delete deleteList.front();
		deleteList.pop_front();
	}
	cout << "Freed " << r << " race(s). " << sizeof(Race) * r << " bytes." << endl;
	
	return gs;
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
	std::unordered_map<std::string, int> scores, ties;
	
	for (auto it = players.cbegin(); it != players.cend(); ++it)
	{
		short int score = getVP(*it);
		scores.insert({ (*it)->name, score });
		
		//should probably use ordered map/sort and find dupes that way
	}
		
	//TODO Determine tie-breakers
	
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
		byte nextNum = p->num + 1;
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
	//TODO assert currentBoard != nullptr
	if (!currentBoard->pass)
	{
		cout << "Playing as: " << currentBoard->name << endl;
		
		//try passing if we haven't already
		//bool firstPass = currentBoard->pass();
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
			cout << "All players pass." << endl;
			//TODO Do all phases here.
			
			cout << "COMBAT PHASE" << endl;
			//COMBAT do all potential combat from all potential actions (using averages?) (starting from sectors numbers IIRC)
			
			cout << "UPKEEP PHASE" << endl;
			//UPKEEP e,m,s balancing
			for (PlayerBoard* l : childState->players)
			{
				byte c = l->getActionCost();
				l->e -= c;
				cout << l->name << " upkeep is " << (int)c << ", leaving " << (int)l->e << endl;
				//TODO if l->e < 0 you bad
				//TODO Reset actions, but not sector inf. discs
			}
			
			cout << "CLEANUP PHASE" << endl;
			//go to next round if there is one
			childState->round++;
			for (PlayerBoard* l : childState->players)
			{
				l->pass = false;
				//do whatever else resets here.
				//reset settler ships
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
