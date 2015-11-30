#pragma once

class Ship;
class Sector;

#include "PlayerBoard.h"
#include "sector.h"

class Ship
{
public:
	enum Type {Interceptor, Cruiser, Dreadnought, Starbase, GCDS};
	Type type;

	int damage;

	PlayerBoard *owner;
	Sector *location;

	Ship();
};
