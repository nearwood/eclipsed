#pragma once

class Ship;
class Sector;

#include "player.h"
#include "sector.h"

class Ship
{
public:
	enum Type {Interceptor, Cruiser, Dreadnought, Starbase, GCDS};
	Type type;

	int damage;

	Player *owner;
	Sector *location;

	Ship();
};
