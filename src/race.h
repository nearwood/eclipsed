#pragma once

class Race;

#include <list>
#include <string>

typedef unsigned char byte;

class Race
{
public:
	enum Color {Red, Green, Blue, Yellow, White, Black} color;
	
	byte e, m, s; //starting economy, minerals, science
	byte moves, builds, upgrades;
	//byte buildCost...
	byte rep, dip; //reputation and diplomacy tile spots
	byte sector;
	
	std::string name;
	
	Race();
	//Race(const Race& other);
};
