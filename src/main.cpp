//#include <QApplication>

//#include "mainwindow.h"

#include <iostream>
#include <fstream>

#include "json/json.h"

#include "game.h"

#define GD_RACES "../data/races.json"

using namespace std;

int main(int argc, char *argv[])
{
	ifstream ifs;
	Json::Value races;
	
	cout << "eclipsed alpha" << endl;
	
	cout << "Loading game files..." << endl;
	ifs.open(GD_RACES, ifstream::in);
	if (!ifs.is_open())
	{
		cerr << "Unable to load game file: " << GD_RACES << endl;
		return -1;
	}
	
	Json::Reader rdr;
	rdr.parse(ifs, races, false);
	
	cout << "Loading game configuration..." << endl;
	
	return 0;
	
    //QApplication a(argc, argv);
    //ainWindow w;
    //w.show();
    //return a.exec();

}
