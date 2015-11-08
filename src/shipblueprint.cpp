#include "shipblueprint.h"

ShipBlueprint::ShipBlueprint()
{

}

int ShipBlueprint::getHP()
{
	return this->hullPoints + 1;
}
