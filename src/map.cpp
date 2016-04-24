#include "map.h"

#include <iostream>
#include <cmath>

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

Map::Map(const Map& other)
{
	//Map();
	
	gc = new Sector(*(other.gc)); //TODO Why do i even need this?
	
	for (Sector* s : other.sectors)
		sectors.push_back(new Sector(*s));
		
	for (Sector* s : other.availableSectors)
		availableSectors.push_back(new Sector(*s));
	
	//TODO Eventually we can take advantage of the fact that once sectors are placed in the game, they do not move (children of states can just shallow copy board)
	
	
	//Fill out graph
}

void Map::setAvailableSectors(std::vector<Sector> sectorList)
{
	availableSectors.clear(); //TODO deep pointer clear... but this shouldn't really be called more than once
	
	for (Sector s : sectorList)
		availableSectors.push_back(new Sector(s)); //TODO sort or someshit
}

short int Map::size()
{
	return sectors.size(); //ideally this should be the filled graph size, not just what was loaded.
}

//Get a list of available sectors, one for each free location around s
std::vector<Sector*> Map::getPotentialAdjacentSectors(Sector& s)
{//TODO Randomly pick sector from each ring that is in or adjacent to s
	//Note that any index pointer could be null if the available sectors for that ring are empty
	std::vector<Sector*> pot;
	int ring[6];
	Sector* a;
	
	ring[0] = Map::getRing(s.q + 1, s.r, s.s);
	ring[1] = Map::getRing(s.q, s.r + 1, s.s);
	ring[2] = Map::getRing(s.q, s.r, s.s + 1);
	ring[3] = Map::getRing(s.q - 1, s.r, s.s);
	ring[4] = Map::getRing(s.q, s.r - 1, s.s);
	ring[5] = Map::getRing(s.q, s.r, s.s - 1);
	
	for (int i = 0; i < 6; ++i)
	{
		if (ring[i] > 3) ring[i] = 3;
		
		switch (ring[i])
		{
			case 1:
			a = getRandomRingSector(1);
			break;
			
			case 2:
			a = getRandomRingSector(2);
			break;
			
			case 3:
			a = getRandomRingSector(3);
			break;
			
			default:
			break;
		}
		
		if (a != nullptr)
		{
			switch (i) //lol
			{
				case 0:
				a->q = s.q + 1; a->r = s.r; a->s = s.s;
				break;
				case 1:
				a->q = s.q; a->r = s.r + 1; a->s = s.s;
				break;
				case 2:
				a->q = s.q; a->r = s.r; a->s = s.s + 1;
				break;
				case 3:
				a->q = s.q - 1; a->r = s.r; a->s = s.s;
				break;
				case 4:
				a->q = s.q; a->r = s.r - 1; a->s = s.s;
				break;
				case 5:
				a->q = s.q; a->r = s.r; a->s = s.s - 1;
				break;
			}
			
			pot.push_back(a);
		}
	}
	
	return pot;
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

std::vector<Sector*> Map::getAllSectors()
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

std::vector<Sector*> Map::getRingSectors(int ring)
{
	std::vector<Sector*> ringSectors;
	
	for (Sector* s : availableSectors)
		if (s->ring == ring) ringSectors.push_back(s);
		
	return ringSectors;
}

Sector* Map::getRandomRingSector(int ring)
{
	std::vector<Sector*> ringSectors = getRingSectors(ring);
	switch (ringSectors.size())
	{
		case 0:
		return nullptr;
		
		case 1:
		return ringSectors[0];
		
		default:
		int r = rand() % ringSectors.size();
		return ringSectors[r];
	}
}

int Map::getRing(int q, int r, int s)
{//TODO consolidate this with sector distance
	return std::max(std::max(abs(q), abs(r)), abs(s));
}

Map::~Map()
{
	delete gc;
	
	for (Sector* s : sectors)
		delete s;
		
	for (Sector* s : availableSectors)
		delete s;
}
