#include "PlayerBoard.h"

#include <iostream>

using namespace std;

std::map<byte, byte> PlayerBoard::actionCost = {{1, 0}, {2, 0}, {3, 1}, {4, 2}, {5, 3}, {6, 5}, {7, 7}, {8, 10}, {9, 13}, {10, 17}, {11, 21}, {12, 25}, {13, 30}};

PlayerBoard::PlayerBoard(Race& r)
:race(r),
pass(false)
{
	this->name = r.name;
	this->e = r.e;
	this->m = r.m;
	this->s = r.s;
	
	for (int d = 1; d <= 13; ++d) //TODO add up to +3 later
	{
		inf.push_back(new Disc(this, nullptr));
	}
}

PlayerBoard::PlayerBoard(PlayerBoard& other):
race(other.race),
num(other.num),
pass(other.pass),
colonies(other.colonies),
e(other.e),
m(other.m),
s(other.s),
name(other.name)
{
	inf = other.inf;
	
	//std::list<Disc*> infAvailable, infSpent;
	//std::list<Ship*> deployedShips, unbuiltShips;
}

Disc* PlayerBoard::getFreeInfluence()
{
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if ((*it)->isFree()) return *it;
		
	return nullptr;
}

void PlayerBoard::placeInfluence(Sector* s)
{
	//TODO Can I just use vector<Disc> instead of pointers since it returns refs?
	Disc* d = getFreeInfluence();
	if (d != nullptr)
	{
		cout << "Placing " << this->name << " influence disc on sector " << s->id << endl;
		d->setSector(s);
	}
}

byte PlayerBoard::getActionCost()
{
	short int spent = 0;
	for (auto it = inf.cbegin(); it != inf.cend(); ++it)
		if (!(*it)->isFree()) spent++;
		
	//TODO will want to revisit this
	short int excess = inf.size() - 13;
	spent -= excess;
	if (spent < 0) spent = 0;
	
	return actionCost.at(spent);
}
