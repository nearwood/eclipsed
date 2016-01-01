#include "PlayerBoard.h"

PlayerBoard::PlayerBoard(Race& r)
:race(r),
pass(false)
{

}

PlayerBoard::PlayerBoard(PlayerBoard& other)
:race(other.race),
num(other.num),
pass(other.pass),
colonies(other.colonies),
e(other.e),
m(other.m),
s(other.s),
name(other.name)
{
	//std::list<Disc*> infAvailable, infSpent;
	//std::list<Ship*> deployedShips, unbuiltShips;
}
