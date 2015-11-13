//#include <QApplication>

//#include "mainwindow.h"

#include <iostream>
#include <fstream>
#include <pthread.h>

#include "json/json.h"

#include "game.h"

#define GD_RACES "../data/races.json"

using namespace std;

void gameRunner(Json::Value setup)
{
	
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
	
	//load what the user has input for a set of games
	//# players, races, iterations, player difficulty
	
	//Could bring Qt back and use QThreads
	
	iret1 = pthread_create(&gameThread, NULL, gameRunner, (void*)setup);
	if (iret1)
	{
		//fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		//exit(EXIT_FAILURE);
		
		cout << "Game parameters..." << endl;
		Game game(setup);
		//setup races, techs (for number of players), decide first player, etc.
		
		cout << "Simulating..." << endl;
		//start timing and go through each turn, and each phase each turn until victory
		game.play(); //TODO some kind of while (1), but with some feedback and system.process() or whatever
		//preferably in another thread
	}
	
	return 0;
	
	//QApplication a(argc, argv);
	//ainWindow w;
	//w.show();
	//return a.exec();
}
