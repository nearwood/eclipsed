#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(Race& r)
:race(r),
pass(false)
{
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
		d->setSector(s);
	}
}
