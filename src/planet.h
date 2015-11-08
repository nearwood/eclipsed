#ifndef PLANET_H
#define PLANET_H

#include <list>

#include "resource.h"

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
