#include "PlayerBoard.h"

#include <iostream>

using namespace std;

//TODO externalize this (might not be same between boards)
std::map<byte, byte> PlayerBoard::actionCost = {{1, 0}, {2, 0}, {3, 1}, {4, 2}, {5, 3}, {6, 5}, {7, 7}, {8, 10}, {9, 13}, {10, 17}, {11, 21}, {12, 25}, {13, 30}};

PlayerBoard::PlayerBoard(Race& r):
race(r),
pass(false)
{
	this->name = r.name;
	this->e = r.e;
	this->m = r.m;
	this->s = r.s;
	
	//TODO externalize # of influence discs
	for (int d = 1; d <= 6; ++d) //13, TODO add up to +3 later
	{
		inf.push_back(new Disc(this, 0));
	}
}

PlayerBoard::PlayerBoard(PlayerBoard& other):
race(other.race),
num(other.num),
pass(other.pass),
colonyShips(other.colonyShips),
usedColonyShips(other.usedColonyShips),
e(other.e),
m(other.m),
s(other.s),
name(other.name)
{
	for (Disc* d : other.inf)
	{
		inf.push_back(new Disc(this, d->getSector(), d->isUsed()));
	}
	
	//std::list<Disc*> infAvailable, infSpent;
	//std::list<Ship*> deployedShips, unbuiltShips;
}

short int PlayerBoard::getRemainingActions()
{
	short int a = 0;
	
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if ((*it)->isFree()) a++;
		
	return a;
}

Disc* PlayerBoard::getFreeInfluence()
{
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if ((*it)->isFree()) return *it;
		
	return nullptr;
}

std::vector<Disc*> PlayerBoard::getPlacedInfluence() //should be plural
{
	std::vector<Disc*> pi;
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if ((*it)->isPlaced()) pi.push_back(*it);
		
	return pi;
}

void PlayerBoard::placeInfluence(Sector* s)
{
	//TODO Can I just use vector<Disc> instead of pointers since it returns refs?
	Disc* d = getFreeInfluence();
	if (d != nullptr)
	{
		//cout << "Placing " << this->name << " influence disc on sector " << s->id << endl;
		d->setSector(s->id);
	}
}

void PlayerBoard::roundCleanup()
{
	this->pass = false;
	this->usedColonyShips = 0;
	
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if ((*it)->isUsed()) (*it)->free();
}

byte PlayerBoard::getActionCost()
{
	short int spent = 0;
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if (!(*it)->isFree()) spent++;
		
	//TODO will want to revisit this
	//short int excess = 13 - inf.size();
	//spent -= excess;
	//if (spent < 0) spent = 0;
	
	return actionCost.at(spent);
}

short int PlayerBoard::getVP(Map* map)
{
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
	the Descendants and Planta benefit from their species-spe­cific
	fast expansion capabilities and are thus stronger than
	other species in a two-player setting. It is recommended
	not to use these species in a two player game.
	
	In case of a tie, the total amount of Resources (Money, Science
	and Materials) in each tied player’s Storage is the tie breaker.
	*/
	
	//Hexes with an influence disc
	short int vp = 0;
	std::vector<Disc*> pi = this->getPlacedInfluence();
	for (auto it = pi.cbegin(); it != pi.cend(); ++it)
	{
		//TODO Uuuuugggh had to pull a map reference to this class just for this line
		Sector* loc = map->getPlacedSectorById((*it)->getSector());
		vp += loc->vp;
	}
	
	return vp;
}

PlayerBoard::~PlayerBoard()
{//valgrind keeps complaining that im trying to free already freed mem.... TODO
	for (Disc* d : inf)
		delete d;
	
	for (Ship* d : deployedShips)
		delete d;
	
	for (Ship* d : unbuiltShips)
		delete d;
	
}
