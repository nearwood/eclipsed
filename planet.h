#ifndef PLANET_H
#define PLANET_H

#include <QList>

#include "resource.h"

class Planet
{
public:
	enum ResourceType { ANY, MINERALS, SCIENCE, ECONOMY };
	ResourceType resourceType;

	bool isOrbital; //orbitals can only be science/economy IIRC

	QList<Resource> resources;

    Planet();
};

#endif // PLANET_H
