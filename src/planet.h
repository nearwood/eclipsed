#ifndef PLANET_H
#define PLANET_H

#include <list>

#include "resource.h"

//TODO Don't think this is needed--except maybe when trying to wipe out other players...
// but even then we can just gather aeco + eco, for example.
class Planet
{
public:
	enum ResourceType { ANY, MINERALS, SCIENCE, ECONOMY };
	ResourceType resourceType;

	bool isOrbital; //orbitals can only be science/economy IIRC

	std::list<Resource> resources;

    Planet();
};

#endif // PLANET_H
