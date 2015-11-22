//#include <QApplication>

//#include "mainwindow.h"

#include <iostream>
#include <fstream>

#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

#include "json/json.h"

#include "game.h"

#define GD_RACES "../data/races.json"

using namespace std;

void* gameRunner(void* g)
{
	cout << "Simulation thread start..." << endl;
	Game* game = (Game*)g;
	//start timing and go through each turn, and each phase each turn until victory
	cout << "Simulating..." << endl;
	game->play(); //TODO some kind of while (1), but with some feedback and system.process() or whatever
	
	delete game;
}

int main(int argc, char *argv[])
{
	ifstream ifs;
	Json::Value races, setup;
	
	if (argc <= 1)
	{
		cout << "eclipsed" << endl;
		cout << "Usage: " << argv[0] << " <game.json>" << endl;
		return 0;
	}
	
	cout << "Loading game files..." << endl;
	ifs.open(GD_RACES);//, ifstream::in);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game file: " << GD_RACES << endl;
		return -1;
	}
	
	Json::Reader rdr;
	rdr.parse(ifs, races, false);
	ifs.close();
	
	//load all game constants
	
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
	Game* game = new Game(GameState::fromJson(setup));
	//setup races, techs (for number of players), decide first player, etc.
	
	//load what the user has input for a set of games
	//# players, races, iterations, player difficulty
	
	//Could bring Qt back and use QThreads
	
	thread gameThread(gameRunner, game);
	
	gameThread.join();
	
	return 0;
	
	//QApplication a(argc, argv);
	//ainWindow w;
	//w.show();
	//return a.exec();
}
