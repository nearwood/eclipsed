#include "map.h"

#include <iostream>

//Sector* Map::NullSector = new Sector();

Map::Map()
{//eh, is this only for the null sector?
	//Fill graph
	//Ring 0
	/*  __
	 * / x\
	 * \__/
	 */
	
	/* Ring 1
	 *     __
	 *  __/ q\__
	 * / r\__/ s\
	 * \__/  \__/
	 * /-s\__/-r\
	 * \__/-q\__/
	 *    \__/
	 */
	
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
	 
	//For ring 3, since we can add sectors at d >= 3, the idea is that we just handle them on a case-by-case basis.
}

Map::Map(Map& other)
{
	Map();
	//for (auto it = other.sectors.begin(); it != other.sectors.cend(); ++it)
	//	sectors.push_back(new Sector(**it));
	//sectors = other.sectors;
	
	//TODO Deep copy of availableSectors & sectors
	//TODO Advanced copies just a diff??!?!
	//gc = new Sector(*(other.gc));
	
	//Fill out graph
}

void Map::setAvailableSectors(std::list<Sector*> s)
{
	availableSectors = s; //TODO sort or someshit
}

short int Map::size()
{
	return sectors.size(); //ideally this should be the filled graph size, not just what was loaded.
}

//Get a list of available sectors, one for each free location around s
std::list<Sector*> Map::getPotentialAdjacentSectors(Sector& s)
{
	//TODO Randomly pick sector from each ring that is in or adjacent to s
	return std::list<Sector*>();
}

void Map::placeSector(Sector* s) //TODO Orientation
{
	//if (s->startSector) //place in ring 2
	for (auto it = availableSectors.cbegin(); it != availableSectors.cend(); ++it)
	{
		if ((*it)->id == s->id)
		{
			std::cout << "Placing sector at: (" << s->q << ", " << s->r << ", " << s->s << ")" << std::endl;
			sectors.push_back(s);
			//TODO link to other sectors
			availableSectors.erase(it);
			break;
		}
	}
}

std::list<Sector*> Map::getAllSectors()
{
	return this->sectors;
}

Sector* Map::getAvailableSectorById(short int id)
{//TODO first digit is ring
	for (auto it = availableSectors.cbegin(); it != availableSectors.cend(); ++it)
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
