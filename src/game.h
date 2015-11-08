#ifndef GAME_H
#define GAME_H

#include "sector.h"
#include "ship.h"
#include "player.h"

#include <list>

class Game
{
public:
	std::list<Player> players;
	std::list<Sector> sectors;
	
	Game();
};

#endif // GAME_H
