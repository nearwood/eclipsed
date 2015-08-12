#ifndef SHIPBLUEPRINT_H
#define SHIPBLUEPRINT_H

#include "ship.h"

class ShipBlueprint
{
public:
	Ship::Type type;

	int initiative;
	int hullPoints;

	int computer;
	int shield;

	int ionCannon, ionTurret;
	int plasmaCannons;
	int antimatter;
	int ionMissiles;
	int plasmaMissiles;

	int getHP();

	ShipBlueprint();
};

#endif // SHIPBLUEPRINT_H
