#include "PlayerBoard.h"

PlayerBoard::PlayerBoard()
:pass(false)
{

}

PlayerBoard::PlayerBoard(const PlayerBoard& other)
:num(other.num),
pass(other.pass),
colonies(other.colonies),
color(other.color),
e(other.e),
m(other.m),
s(other.s),
name(other.name)
{
	//std::list<Disc*> infAvailable, infSpent;
	//std::list<Ship*> deployedShips, unbuiltShips;
}
