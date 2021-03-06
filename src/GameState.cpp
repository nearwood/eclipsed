
#include "GameState.h"

#include <iostream>
#include <vector>

using namespace std;

short int GameState::lastRound = 0;

GameState::GameState()
:round(0)
{
	map = new Map();
}

GameState::GameState(GameState& other)
:currentPlayer(other.currentPlayer),
firstPlayer(other.firstPlayer),
lastFirstPlayer(other.lastFirstPlayer),
round(other.round),
depth(other.depth + 1),
numChildren(0)
{
	map = new Map(*(other.map));
	
	for (auto it = other.players.cbegin(); it != other.players.cend(); ++it)
		players.push_back(new PlayerBoard(**it));
	
	tech = other.tech;
	
	//children remains empty
}

GameState::~GameState()
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		delete *it;
		
	delete map;
}

//Initial state... TODO any state (!)
GameState* GameState::fromJson(Json::Value& races, Json::Value& sectors, Json::Value& initialState)
{
	GameState* gs = new GameState();
	
	gs->round = 1;
	gs->depth = 0;
	gs->numChildren = 0;
	
	GameState::lastRound = initialState["rounds"].asInt();
	
	//load all races
	//load game json, players, and assign playerboards with race
	//delete unused races
	std::list<Race*> racesList; //TODO no need for pointers
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
		r->trade = jr["trade"].asInt();
		r->name = jr.get("name", "UNKNOWN").asString();
		racesList.push_back(r);
	}
	cout << "Loaded " << racesList.size() << " races. " << sizeof(Race) * racesList.size() + sizeof(racesList) << " bytes." << endl;
	
	std::vector<Sector> sectorList;
	const Json::Value sectorsJson = sectors["sectors"];
	for (uint i = 0; i < sectorsJson.size(); ++i)
	{
		Json::Value js = sectorsJson[i];
		Sector s(-1, -1, -1);
		s.ring = js["ring"].asInt();
		s.id = js["id"].asInt();
		s.vp = js["vp"].asInt();
		s.ancientSpawn = js["ancient"].asBool();
		s.startSector = js["startSector"].asBool();
		
		Json::Value squares = js["squares"];
		//assert storage.size() == 3
		s.eco = squares[0].asInt();
		s.min = squares[1].asInt();
		s.sci = squares[2].asInt();
		
		Json::Value advSquares = js["advancedSquares"];
		//assert storage.size() == 3
		s.aeco = advSquares[0].asInt();
		s.amin = advSquares[1].asInt();
		s.asci = advSquares[2].asInt();
		
		//s.name = js.get("name", "UNKNOWN").asString();
		sectorList.push_back(s);
	}
	gs->map->setAvailableSectors(sectorList);
	cout << "Loaded " << sectorList.size() << " sectors. " << sizeof(Sector) * sectorList.size() + sizeof(sectorList) << " bytes." << endl; //TODO recheck
	
	//Get Galactic Center
	Sector* sector = gs->map->getAvailableSectorById(1);
	sector->q = 0;
	sector->r = 0;
	sector->s = 0;
	gs->map->placeSector(sector->id);
	gs->map->setGalacticCenter(sector); //TODO grumble...
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
		gs->map->placeSector(sector->id);
		pb->placeInfluence(sector);
		pb->colonyShips = 3;
		pb->usedColonyShips = 0;
	}
	
	//Probably a better way but this is done once per game so who cares.
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
	if (round > GameState::lastRound) return true;
	
	return false;
}

//TODO Need to fix bug with tie breaking, doesn't handle when score is tied between more than 2 players
std::unordered_map<std::string, int> GameState::getScores()
{
	std::unordered_map<std::string, int> scores;
	std::unordered_map<int, PlayerBoard*> ties;
	
	//cout << "Calculating scores..." << endl;
	for (auto it = players.cbegin(); it != players.cend(); ++it)
	{//Get each players raw VP
		int score = (*it)->getVP(this->map);
		scores[(*it)->name] = score;
		//cout << (*it)->name << ": " << score << endl;
		
		//TODO below check might be wrong, need to think through >2 players with same score
		//Check if we are tied to anyone else
		auto found = ties.find(score);
		if (found == ties.cend())
		{//if not, insert this for comparison later
			ties.insert({ score, (*it) });
			//cout << "notie: " << (*it)->name << ": " << score << endl;
		}
	}
	
	for (auto it = players.cbegin(); it != players.cend(); ++it)
	{//Find any ties
		int score = scores[(*it)->name];
		
		auto found = ties.find(score);
		if (found == ties.cend())
		{//no tie, so this is final score
			scores[(*it)->name] = score;
			//cout << (*it)->name << ": " << score << endl;
		}
		else
		{//Tie with another player, add E, M, S to score
			//This adjusted score is just to settle ties between the tied players, otherwise untied players are at a disadvantage
			//For clarity, this should ideally be separate from VP, but we will just add it to the VP for now
			
			//insert tied with player score
			PlayerBoard* pb = found->second;
			if (pb != (*it))
			{
				//short int score2 = pb->getVP(this->map);
				//score2 += pb->e + pb->m + pb->s;
				//scores[pb->name] = score2;
				
				//insert this player's score
				//score += (*it)->e + (*it)->m + (*it)->s;
				//scores[(*it)->name] = score;
				//cout << "tie: " << (*it)->name << ": " << score << " + " << (*it)->e + (*it)->m + (*it)->s << endl;
				//cout << "tie: " << pb->name << ": " << score2 << " + " << pb->e + pb->m + pb->s << endl;
				//And if it's still a tie at this point, tough.
			}
		}
		
		//should probably use ordered map/sort and find dupes that way
	}
		
	//TODO Determine tie-breakers
	
	return scores;
}

PlayerBoard* GameState::getPlayer(string name)
{
	for (auto it = players.cbegin(); it != players.cend(); ++it)
		if ((*it)->name == name) return *it;
	
	return nullptr;

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
		if ((*it)->isActive() && !(*it)->pass) return false;
	
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
	static int totalStatesGenerated = 0;
	
	std::list<GameState*> children;
	
	PlayerBoard* currentBoard = parent.getCurrentPlayer();
	if (!currentBoard->isActive())
	{
		return children;
	};
	
	//TODO assert childBoard != nullptr
	if (!currentBoard->pass)
	{
		cout << "Playing as: " << currentBoard->name << " [" << (int)currentBoard->e << ", " << (int)currentBoard->m << ", " << (int)currentBoard->s << "]" << endl;
		
		//cout << "+PASS" << endl;
		GameState* childState = new GameState(parent); //TODO Shouldn't we use parent first? Or parent is already 'done'?
		PlayerBoard *childBoard = childState->getCurrentPlayer();
		
		//try passing if we haven't already
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
			//cout << "Setting first player token" << endl;
			childState->lastFirstPlayer = childState->firstPlayer;
			childState->firstPlayer = childBoard->name;
		}
		
		//going to have to force a pass at some point, preferably soon after e < 0 as you cannot action all your owned space away, and there are diminishing returns up to that point.
		
		PlayerBoard *nextPlayer = childState->getNextPlayer();
		childState->currentPlayer = nextPlayer->name; //TODO Null check?
		children.push_back(childState);
		
		//Try moves until actions run out
		Disc* d = currentBoard->getFreeInfluence(); //just need to check, no need to get
		if (d != nullptr)
		{
			//EXPLORE
			//To explore, a player can place sectors next to any sectors with unpinned ships, or sectors with their influence placed.
			//Also, TODO find out and implement if the player can select 3 random tiles and place 1 or is that another board game?
			
			//Find out sectors where we have influence discs placed
			std::vector<Disc*> placedInf = currentBoard->getPlacedInfluence();
			//cout << "Checking placed influence: " << placedInf.size() << endl;
			
			for (auto it = placedInf.cbegin(); it != placedInf.cend(); ++it)
			{//For each placed influence //TODO Also for any 'unpinned' ships
				Sector* sectorA = parent.map->getPlacedSectorById((*it)->getSector());
				
				//TODO Branch to one child for each (available) ring
				int r = rand() % 3 + 1; //Player must choose ONE ring to pick from
				std::vector<Sector*> adjacentSectors = parent.map->getPotentialAdjacentSectors(*sectorA, r);
				//cout << " ^- adjacent sectors: " << adjacentSectors.size() << endl; 
				
				for (Sector* s : adjacentSectors)
				{//For all 'empty' sector positions around the sector with a placed influence disc
					if (s == nullptr) continue; //Why would it be null?
					
					//Place sector without placing influence
					GameState* cs = new GameState(parent);
					Sector* newSector = cs->map->getAvailableSectorById(s->id);
					PlayerBoard* cb = cs->getCurrentPlayer();
					Disc* freeInf = cb->getFreeInfluence(); //This won't be null since parent had one free
					freeInf->use(); //use influence for explore action
					cs->map->placeSector(newSector->id);
					//cout << "+EXPLORE: @(" << newSector->q << ", " << newSector->r << ", " << newSector->s << ")" << endl; //<< newSector << " free influence: " << cb->getRemainingActions() << endl;
					PlayerBoard *nextPlayer = cs->getNextPlayer();
					cs->currentPlayer = nextPlayer->name;
					children.push_back(cs);
					
					//TODO Discarding into face up pile
					
					//Here we use the childBoard to check if there's an *additional* influence token available
					freeInf = cb->getFreeInfluence();
					if (freeInf != nullptr)
					{
						//cout << "USED COLONY SHIPS: " << cb->usedColonyShips << endl;
						//Place influence and flip colonize token
						cs = new GameState(*cs); //Note this is a copy of the previous child state, not parent.
						cb = cs->getCurrentPlayer();
						freeInf = cb->getFreeInfluence(); //Reassign influence from this new state
						//If we have free influence and an unused colony ship left
						if (freeInf != nullptr && cb->usedColonyShips < cb->colonyShips)
						{//TODO Might be redundant since we check parent
							newSector = cs->map->getPlacedSectorById(s->id);
							freeInf->setSector(newSector->id);
							cb->usedColonyShips++; //"flip" colony ship or whatever that thing is
							//cout << "+INFLUENCE: " << newSector << " free influence: " << cb->getRemainingActions() << endl;
							PlayerBoard *nextPlayer = cs->getNextPlayer();
							cs->currentPlayer = nextPlayer->name;
							children.push_back(cs);
						}
						else
						{//delete state, we didn't need to create it
							delete cs; //TODO delete entire composition thru dtr
						}
					}
				}
			}
			
			//TODO any other actions for this free influence
		}
	}
	else
	{
		if (parent.allPlayersPass())
		{//If last pass, end the round
			cout << "All players pass. Round " << parent.round << " over." << endl;
			//TODO Do all phases here.
			
			//cout << "COMBAT PHASE" << endl;
			//COMBAT do all potential combat from all potential actions (using averages?) (starting from sectors numbers IIRC)
			
			//cout << "UPKEEP PHASE" << endl;
			//UPKEEP e,m,s balancing
			
			for (PlayerBoard* l : parent.players)
			{
				char c = l->getActionCost();

				if (c > l->e)
				{//if cost is more than economy
					//trade m,s to try and make up difference
					short int extra = (l->m + l->s) / l->race.trade;
					//TODO incremental m,s sacrifice
					if (extra + l->e >= c)
					{//cost is ok this turn
						GameState* cs = new GameState(parent);
						PlayerBoard* p = cs->getPlayer(l->name);
						//cout << "+TRADE: trading down m, s" << endl;
						p->m = p->s = 0;
						p->e += extra - c;
						cs->roundCleanup();
						PlayerBoard *nextPlayer = cs->getNextPlayer();
						cs->currentPlayer = nextPlayer->name;
						children.push_back(cs);
					}
					else
					{//trading isn't enough
						//cout << "+RAZE: Not implemented" << endl;
						//TODO raze discs, and if that's not enough, player is out of game
						GameState* cs = new GameState(parent);
						PlayerBoard* p = cs->getPlayer(l->name);
						std::vector<Disc*> placedInfluence = p->getPlacedInfluence();
						
						while (placedInfluence.size() > 0)
						{
							Disc *d = placedInfluence.back();
							p->razeSector(d);
							placedInfluence.pop_back();
							
							if (p->getActionCost() < (extra + l->e))
							{
								break;
							}
						}
						
						if (placedInfluence.size() == 0 && p->getActionCost() > (extra + l->e))
						{
							cout << l->name << " bankrupt and removed from game." << endl;
							p->removeFromGame();
						}
						
						
						//cout << l->name << " bankrupt. Razing colonies?" << endl;
						cs->roundCleanup();
						PlayerBoard *nextPlayer = cs->getNextPlayer();
						cs->currentPlayer = nextPlayer->name;
						children.push_back(cs);
					}
				}
				else
				{
					GameState* cs = new GameState(parent);
					PlayerBoard* p = cs->getPlayer(l->name);
					p->e -= c;
					//cout << "+CLEANUP" << endl;
					cs->roundCleanup();
					PlayerBoard *nextPlayer = cs->getNextPlayer();
					cs->currentPlayer = nextPlayer->name;
					children.push_back(cs);
					//cout << p->name << " upkeep is " << (int)c << ", leaving " << (int)p->e << endl;
				}

				//TODO if not out of red and no discs to remove, game over--calc score.
				//TODO Reset actions, but not sector inf. discs
			}
		}
		else
		{//This player has passed but not all players have
			//reactions
			//build, upgrade, move
		}
	}
	
	totalStatesGenerated += children.size();
	//parent.numChildren += children.size();
	//cout << "+ Tree Depth: " << parent.depth << endl;
	//cout << "+ Tree Breadth: " << parent.numChildren << endl;
	//cout << "+ Generated " << children.size() << " child states. " << sizeof(GameState) * children.size() + sizeof(children) << " bytes." << endl;
	//cout << "+ Total States: " << totalStatesGenerated << ". " << sizeof(GameState) * totalStatesGenerated << " bytes." << endl;
	return children;
}

void GameState::roundCleanup()
{
	//cout << "CLEANUP PHASE" << endl;
	//go to next round if there is one
	this->round++;
	for (PlayerBoard* l : this->players)
	{
		l->roundCleanup();
		//do whatever else resets here.
	}
}

