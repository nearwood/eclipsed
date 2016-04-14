#include "map.h"

Sector* Map::NullSector = new Sector();

Map::Map()
{//eh, is this only for the null sector?
	//sectors = std::list<Sector*>();
	
	//Fill graph
	//Ring 0
	/*  __
	 * / x\
	 * \__/
	 */
	gc = new Sector(); //galactic core is never empty
	//TODO setup GC cubes and defenses
	
	/* Ring 1
	 *     __
	 *  __/ x\__
	 * / x\__/ x\
	 * \__/  \__/
	 * / x\__/ x\
	 * \__/ x\__/
	 *    \__/
	 */
	for (int i = 0; i < 6; ++i)
	{
		//gc->nbr[i] = Sector::createEmptySector(1);
	}
	
	/* Ring 2 - 2(6) sectors
	 *        __
	 *     __/ x\__
	 *  __/ x\__/ x\__
	 * / x\__/  \__/ x\
	 * \__/  \__/  \__/
	 * / x\__/  \__/ x\
	 * \__/  \__/  \__/
	 * / x\__/  \__/ x\
	 * \__/ x\__/ x\__/
	 *    \__/ x\__/
	 *       \__/
	 */
	for (int i = 0; i < 6; ++i)
	{
		//gc->nbr[0]-> = Sector::createEmptySector(2);
	}
	
	//TODO Worth it to have sectors figure this out on their own?
	
	/* Ring 3 - 3(6)
	 *           __
	 *        __/ x\__
	 *     __/ x\__/ x\__
	 *  __/ x\__/  \__/ x\__
	 * / x\__/  \__/  \__/ x\
	 * \__/  \__/  \__/  \__/
	 * / x\__/  \__/  \__/ x\
	 * \__/  \__/  \__/  \__/
	 * / x\__/  \__/  \__/ x\
	 * \__/  \__/  \__/  \__/
	 * / x\__/  \__/  \__/ x\
	 * \__/ x\__/  \__/ x\__/
	 *    \__/ x\__/ x\__/
	 *       \__/ x\__/
	 *          \__/
	 */
	for (int i = 0; i < 6; ++i)
	{
		//gc->nbr[i] = Sector::createEmptySector(2);
	}
}

Map::Map(Map& other)
{
	Map();
	//for (auto it = other.sectors.begin(); it != other.sectors.cend(); ++it)
	//	sectors.push_back(new Sector(**it));
	sectors = other.sectors;
	
	gc = other.gc;
	
	//Fill out graph
}

void Map::setSectors(std::list<Sector*> s)
{
	sectors = s; //TODO sort or someshit
}

short int Map::size()
{
	return sectors.size(); //ideally this should be the filled graph size, not just what was loaded.
}

void Map::placeSector(Sector* s)
{
	//uhhhh need null sectors
}

std::list<Sector*> Map::getAllSectors()
{
	return this->sectors;
}

Sector* Map::getSectorById(short int id)
{
	for (auto it = sectors.cbegin(); it != sectors.cend(); ++it)
		if ((*it)->id == id) return (*it);
		
	return nullptr;
}

//Sector* Map::getGalacticCenter() { return this->gc; }
std::list<Sector*> Map::getRing1Sectors()
{
	return std::list<Sector*>();
}

std::list<Sector*> Map::getRing2Sectors()
{
	return std::list<Sector*>();
}

std::list<Sector*> Map::getRing3Sectors()
{
	return std::list<Sector*>();
}

Sector* Map::getRandomRing1Sector()
{
	return nullptr;
}

Sector* Map::getRandomRing2Sector()
{
	return nullptr;
}

Sector* Map::getRandomRing3Sector()
{
	return nullptr;
}
