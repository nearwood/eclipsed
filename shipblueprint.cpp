#include "shipblueprint.h"

ShipBlueprint::ShipBlueprint()
{

}

ShipBlueprint::getHP()
{
	return this->hullPoints + 1;
}
