#ifndef SHIP_H
#define SHIP_H

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

#endif // SHIP_H
