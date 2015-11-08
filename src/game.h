#pragma once

#include <list>

#include "json/json.h"

#include "sector.h"
#include "ship.h"
#include "player.h"

class Game
{
public:
	std::list<Player> players;
	std::list<Sector> sectors;
	
	Game();
	Game(Json::Value setup); //json setup parameters
	void play(); //main loop
};
