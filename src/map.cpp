#include "map.h"

//Sector* Map::NullSector = new Sector();

Map::Map()
{//eh, is this only for the null sector?
	//sectors = std::list<Sector*>();
	
	//Fill graph
	//Ring 0
	/*  __
	 * / x\
	 * \__/
	 */
	//gc = new Sector(0, 0, 0); //galactic core is never empty
	//gc->id = 1;
	//TODO setup GC cubes and defenses
	//sectors.insert(gc->id, gc);
	//sectors.push_back(gc);
	
	/* Ring 1
	 *     __
	 *  __/ q\__
	 * / r\__/ s\
	 * \__/  \__/
	 * /-s\__/-r\
	 * \__/-q\__/
	 *    \__/
	 */
	//sectors.insert(100, new Sector(1, 0, 0));
	//sectors.insert(010, new Sector(0, 1, 0));
	//sectors.insert(001, new Sector(0, 0, 1));
	//sectors.insert(-100, new Sector(-1, 0, 0));
	//sectors.insert(-010, new Sector(0, -1, 0));
	//sectors.insert(-001, new Sector(0, 0, -1));
	//sectors.push_back(new Sector(1, 0, 0));
	//sectors.push_back(new Sector(0, 1, 0));
	//sectors.push_back(new Sector(0, 0, 1));
	//sectors.push_back(new Sector(-1, 0, 0));
	//sectors.push_back(new Sector(0, -1, 0));
	//sectors.push_back(new Sector(0, 0, -1));
	
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
	//sectors.push_back(new Sector(2, 0, 0));
	//sectors.push_back(new Sector(0, 2, 0));
	//sectors.push_back(new Sector(0, 0, 2));
	//sectors.push_back(new Sector(1, 1, 0));
	//sectors.push_back(new Sector(1, 0, 1));
	//sectors.push_back(new Sector(0, 1, 1));
	//sectors.push_back(new Sector(-2, 0, 0));
	//sectors.push_back(new Sector(0, -2, 0));
	//sectors.push_back(new Sector(0, 0, -2));
	//sectors.push_back(new Sector(-1, -1, 0));
	//sectors.push_back(new Sector(0, -1, -1));
	//sectors.push_back(new Sector(-1, 0, -1));
	
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
	//sectors.push_back(new Sector(3, 0, 0));
	//sectors.push_back(new Sector(-3, 0, 0));
	//sectors.push_back(new Sector(0, 3, 0));
	//sectors.push_back(new Sector(0, -3, 0));
	//sectors.push_back(new Sector(0, 0, 3));
	//sectors.push_back(new Sector(0, 0, -3));
	//sectors.push_back(new Sector(2, 1, 0));
	//sectors.push_back(new Sector(-2, -1, 0));
	//sectors.push_back(new Sector(2, 0, 1));
	//sectors.push_back(new Sector(-2, 0, -1));
	//sectors.push_back(new Sector(0, 2, 1));
	//sectors.push_back(new Sector(0, -2, -1));
	//sectors.push_back(new Sector(1, 2, 0));
	//sectors.push_back(new Sector(-1, -2, 0));
	//sectors.push_back(new Sector(1, 0, 2));
	//sectors.push_back(new Sector(-1, 0, -2));
	//sectors.push_back(new Sector(0, 1, 2));
	//sectors.push_back(new Sector(0, -1, -2));

	//For ring 3, since we can add sectors at d >= 3, the idea is that we just handle them on a case-by-case basis.

	
}

Map::Map(Map& other)
{
	Map();
	//for (auto it = other.sectors.begin(); it != other.sectors.cend(); ++it)
	//	sectors.push_back(new Sector(**it));
	//sectors = other.sectors;
	
	gc = new Sector(other.gc);
	
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
	if (s->startSector)
	{//place in ring 2
		//TODO place evenly according to # of players
		for (auto it = sectors.begin(); it != sectors.end(); ++it)
		{
			if ((*it)->getDistance() == 2 && (*it)->id < 0)
			{
				Sector* d = (*it);
				(*it) = s;
				s->q = d->q;
				s->r = d->r;
				s->s = d->s;
				delete d;
			}
		}
		//TODO can't place
		//TODO This is bad
	}
	else
	{
	}
}

std::list<Sector*> Map::getAllSectors()
{
	return this->sectors;
}

Sector* Map::getSectorById(short int id)
{//TODO first digit is ring
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
