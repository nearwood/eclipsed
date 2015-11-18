//#include <QApplication>

//#include "mainwindow.h"

#include <iostream>
#include <fstream>
#include <pthread.h>

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
}

int main(int argc, char *argv[])
{
	pthread_t gameThread;
	ifstream ifs;
	Json::Value races, setup;
	
	if (argc <= 1)
	{
		cout << "eclipsed alpha" << endl;
		cout << "Usage: " << argv[0] << " <game.json>" << endl;
		return 0;
	}
	
	cout << "Loading game files..." << endl;
	ifs.open(GD_RACES, ifstream::in);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game file: " << GD_RACES << endl;
		return -1;
	}
	
	Json::Reader rdr;
	rdr.parse(ifs, races, false);
	//load all game constants
	
	cout << "Loading game configuration..." << endl;
	
	cout << "Game parameters..." << endl;
	Game* game = new Game(setup);
	//setup races, techs (for number of players), decide first player, etc.
	
	//load what the user has input for a set of games
	//# players, races, iterations, player difficulty
	
	//Could bring Qt back and use QThreads
	
	int iret1 = pthread_create(&gameThread, NULL, gameRunner, (void*)game);
	if (iret1)
	{
		cerr << "Error - pthread_create() return code: " << iret1 << endl;
		//exit(EXIT_FAILURE);
	}
	
	delete game;
	
	return 0;
	
	//QApplication a(argc, argv);
	//ainWindow w;
	//w.show();
	//return a.exec();
}
