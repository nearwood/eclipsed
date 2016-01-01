#pragma once

class Race;

#include <list>
#include <string>

typedef unsigned char sint;

class Race
{
public:
	enum Color {Red, Green, Blue, Yellow, White, Black} color;
	
	sint e, m, s; //starting economy, minerals, science
	sint moves, builds, upgrades;
	//sint buildCost...
	sint rep, dip; //reputation and diplomacy tile spots
	sint sector;
	
	std::string name;
	
	Race();
	//Race(const Race& other);
};
