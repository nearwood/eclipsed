/* eclipsed
 * Copyright (C) 2015 Nicholas Earwood
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//#include <QApplication>

//#include "mainwindow.h"

//C++
#include <iostream>
#include <fstream>

//C++11
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

//C, POSIX
#include <unistd.h>
#include <getopt.h>

#include "json/json.h"

#include "game.h"

#define GD_DIR "../data/"
#define GD_RACES "races.json"
#define GD_SECTORS "sectors.json"
//#define GD_TECH "tech.json"

using namespace std;

/** TODO
 * VERBOSE #define to remove ouput in sim thread
 * shared memory or whatever for ITC.
 * 
 */

void* gameRunner(void* g)
{
	cout << "Simulation thread start." << endl;
	Game* game = (Game*)g;
	//start timing and go through each turn, and each phase each turn until victory
	game->play(); //TODO some kind of while (1), but with some feedback and system.process() or whatever
	cout << "Simulation thread end." << endl;
	
	delete game;
	
	return NULL;
}

int main(int argc, char *argv[])
{
	ifstream ifs;
	Json::Reader rdr;
	Json::Value races, sectors, setup;
	
	if (argc <= 1)
	{
		cout << "eclipsed" << endl;
		cout << "Usage: " << argv[0] << " <game.json>" << endl;
		return 0;
	}
	
	/* argv == --version
	eclipsed version 1, Copyright (C) 2015 Nicholas Earwood
	License GPLv2: GNU GPL version 2 <http://gnu.org/licenses/gpl.html>.
	eclipsed comes with ABSOLUTELY NO WARRANTY, to the extent permitted by law.
	This is free software, and you are welcome to redistribute it
	*/
	
	cout << "Loading game files..." << endl;
	//load all game constants
	ifs.open(GD_DIR GD_RACES);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game file: " << GD_DIR GD_RACES << endl;
		return -1;
	}
	
	rdr.parse(ifs, races, false);
	ifs.close();
	
	//cout << "Loaded races: " << sizeof(races) << " bytes" << endl;
	
	ifs.open(GD_DIR GD_SECTORS);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game file: " << GD_DIR GD_SECTORS << endl;
		return -1;
	}
	
	rdr.parse(ifs, sectors, false);
	ifs.close();
	
	//cout << "Loaded sectors: " << sizeof(sectors) << " bytes" << endl;
	
	cout << "Loading game configuration..." << endl;
	ifs.open(argv[1]);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game setup file: " << argv[1] << endl;
		return -1;
	}
	rdr.parse(ifs, setup, false);
	ifs.close();
	
	cout << "Game parameters..." << endl;
	GameState initialState = GameState::fromJson(setup);
	Game* game = new Game(initialState);
	
	//setup races, techs (for number of players), decide first player, etc.
	
	//load what the user has input for a set of games
	//# players, races, iterations, player difficulty
	
	//Could bring Qt back and use QThreads
	
	thread gameThread(gameRunner, game);
	
	//Do some UI stuff here.
	
	gameThread.join();
	
	//delete all things
	
	return 0;
	
	//QApplication a(argc, argv);
	//ainWindow w;
	//w.show();
	//return a.exec();
}
