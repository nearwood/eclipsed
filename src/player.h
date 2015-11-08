#ifndef PLAYER_H
#define PLAYER_H

class Player;

#include "ship.h"

#include <list>
#include <string>

class Player
{
public:
	std::string name;
	std::string color;

	std::list<Ship> builtShips;
	std::list<Ship> ships;

	Player();
};

#endif // PLAYER_H
