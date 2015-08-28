#ifndef PLAYER_H
#define PLAYER_H

class Player;

#include "ship.h"

#include <QList>

class Player
{
public:
	enum Race {Terran, Mechanima}; //TODO
	enum Color {Blue, Red, Green, Yellow, Black, White};

	Color color;
	Race race;

	QList<Ship> builtShips;
	QList<Ship> ships;

	Player();
};

#endif // PLAYER_H
